#pragma once

void init_hx8357d_board(GDisplay *g);

static GFXINLINE void init_board(GDisplay *g) {
	init_hx8357d_board(g);
}

