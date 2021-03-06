// This file is part of the "pong" project, http://github.com/keithoma/pong>
//   (c) 2019-2019 Christian Parpart <christian@parpart.family>
//   (c) 2019-2019 Kei Thoma <thomakmj@gmail.com>
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#include "score_board.hpp"
#include <sgfx/color.hpp>
#include <sgfx/primitives.hpp>

using namespace sgfx;
using namespace std;

namespace pong {

constexpr int bar_width = 10;
constexpr int bar_padding_width = 10;
constexpr int bar_height = 50;

score_board::score_board(unsigned max_points)
	: canvas{{static_cast<int>(max_points) * (bar_width + bar_padding_width), bar_height}},
	  max_points_{max_points},
	  current_points_{0}
{
	redraw();
}

void score_board::draw_bar(unsigned _n, color::rgb_color _color)
{
	auto const top_left = point{(static_cast<int>(_n) - 1) * (bar_width + bar_padding_width) + 5, 0};
	auto const rect = rectangle{top_left, dimension{10, height()}};

	fill(*this, rect, _color);
}

score_board& score_board::operator++()
{
	if (current_points_ < max_points_)
		draw_bar(++current_points_, color::yellow);

	return *this;
}

score_board& score_board::operator=(unsigned _n)
{
	// Optimizations possible, but overhead trivial.
	current_points_ = _n;
	redraw();

	return *this;
}

void score_board::redraw()
{
	clear(*this, color::black);

	for (unsigned n = 1; n <= current_points_; ++n)
		draw_bar(n, color::yellow);

	for (unsigned n = current_points_ + 1; n <= max_points_; ++n)
		draw_bar(n, color::gray);
}

}  // namespace pong
