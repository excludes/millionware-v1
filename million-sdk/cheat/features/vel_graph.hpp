#pragma once
#include "../../source engine/sdk.hpp"

namespace velocity_graph {
    // For this example, I will be making a new struct
    // However, you could use std::pair if you want.
    struct velocity_data_t
    {
        int speed;
        bool on_ground;
    };

    inline std::vector<velocity_data_t> data;

    void gather_data( );
	void draw( );
}