#include <gnuradio/buffer_management.hpp>

namespace gr {

void buffer_manager::initialize_buffers(flat_graph_sptr fg,
                                        buffer_factory_function buf_factory,
                                        std::shared_ptr<buffer_properties> buf_props)
{
    // not all edges may be used
    for (auto e : fg->edges()) {
        // every edge needs a buffer
        auto num_items = get_buffer_num_items(e, fg);

        // If buffer has not yet been created, e.g. 1:N block connection
        if (!e->src().port()->buffer()) {

            // If src block is in this domain
            if (std::find(fg->nodes().begin(), fg->nodes().end(), e->src().node()) !=
                fg->nodes().end()) {

                buffer_sptr buf;
                if (e->has_custom_buffer()) {
                    buf = e->buffer_factory()(
                        num_items, e->itemsize(), e->buf_properties());
                } else {
                    buf = buf_factory(num_items, e->itemsize(), buf_props);
                }
                e->src().port()->set_buffer(buf);

                GR_LOG_INFO(_logger, "Edge: {}, Buf: {}", e->identifier(), buf->type());
            }
        } else {
            auto buf = e->src().port()->buffer();
            GR_LOG_INFO(_logger, "Edge: {}, Buf(copy): {}", e->identifier(), buf->type());
        }
    }

    // Assuming all the buffers that the readers will be attaching to have been created at
    // this point.  Will need to handle crossings separately if doing something complex
    for (auto& b : fg->calc_used_blocks()) {
        port_vector_t input_ports = b->input_stream_ports();
        port_vector_t output_ports = b->output_stream_ports();

        for (auto p : input_ports) {
            edge_vector_t ed = fg->find_edge(p);
            if (ed.size() == 0) {
                throw std::runtime_error("Edge associated with input port not found");
            }
            p->set_buffer_reader(ed[0]->src().port()->buffer()->add_reader());
        }
    }
}

int buffer_manager::get_buffer_num_items(edge_sptr e, flat_graph_sptr fg)
{
    size_t item_size = e->itemsize();

    // *2 because we're now only filling them 1/2 way in order to
    // increase the available parallelism when using the TPB scheduler.
    // (We're double buffering, where we used to single buffer)
    size_t nitems = (s_fixed_buf_size * 2) / item_size;

    auto grblock = std::dynamic_pointer_cast<block>(e->src().node());
    if (grblock == nullptr) // might be a domain adapter, not a block
    {
        grblock = std::dynamic_pointer_cast<block>(e->dst().node());
    }

    if (grblock->output_multiple_set()) {
        nitems = std::max(nitems, static_cast<size_t>(2 * (grblock->output_multiple())));
    }

    // If any downstream blocks are decimators and/or have a large output_multiple,
    // ensure we have a buffer at least twice their decimation
    // factor*output_multiple

    auto blocks = fg->calc_downstream_blocks(grblock, e->src().port());

    for (auto& p : blocks) {
        // block_sptr dgrblock = cast_to_block_sptr(*p);
        // if (!dgrblock)
        //     throw std::runtime_error("allocate_buffer found non-gr::block");

        // double decimation = (1.0 / dgrblock->relative_rate());
        double decimation = (1.0 / p->relative_rate());
        int multiple = p->output_multiple();
        nitems = std::max(nitems, static_cast<size_t>(2 * (decimation * multiple)));
        // std::max(nitems, static_cast<int>(2 * (decimation * multiple)));
    }

    return nitems;
}

} // namespace gr
