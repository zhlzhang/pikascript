﻿from PikaObj import *


def __init__(): ...


class EVENT:
    ALL: int
    PRESSED: int
    PRESSING: int
    PRESS_LOST: int
    SHORT_CLICKED: int
    LONG_PRESSED: int
    LONG_PRESSED_REPEAT: int
    CLICKED: int
    RELEASED: int
    SCROLL_BEGIN: int
    SCROLL_END: int
    SCROLL: int
    GESTURE: int
    KEY: int
    FOCUSED: int
    DEFOCUSED: int
    LEAVE: int
    HIT_TEST: int
    COVER_CHECK: int
    REFR_EXT_DRAW_SIZE: int
    DRAW_MAIN_BEGIN: int
    DRAW_MAIN: int
    DRAW_MAIN_END: int
    DRAW_POST_BEGIN: int
    DRAW_POST: int
    DRAW_POST_END: int
    DRAW_PART_BEGIN: int
    DRAW_PART_END: int
    VALUE_CHANGED: int
    INSERT: int
    REFRESH: int
    READY: int
    CANCEL: int
    DELETE: int
    CHILD_CHANGED: int
    CHILD_CREATED: int
    CHILD_DELETED: int
    SCREEN_UNLOAD_START: int
    SCREEN_LOAD_START: int
    SCREEN_LOADED: int
    SCREEN_UNLOADED: int
    SIZE_CHANGED: int
    STYLE_CHANGED: int
    LAYOUT_CHANGED: int
    GET_SELF_SIZE: int
    PREPROCESS: int
    def __init__(self): ...


class ALIGN:
    DEFAULT: int
    TOP_LEFT: int
    TOP_MID: int
    TOP_RIGHT: int
    BOTTOM_LEFT: int
    BOTTOM_MID: int
    BOTTOM_RIGHT: int
    LEFT_MID: int
    RIGHT_MID: int
    CENTER: int
    OUT_TOP_LEFT: int
    OUT_TOP_MID: int
    OUT_TOP_RIGHT: int
    OUT_BOTTOM_LEFT: int
    OUT_BOTTOM_MID: int
    OUT_BOTTOM_RIGHT: int
    OUT_LEFT_TOP: int
    OUT_LEFT_MID: int
    OUT_LEFT_BOTTOM: int
    OUT_RIGHT_TOP: int
    OUT_RIGHT_MID: int
    OUT_RIGHT_BOTTOM: int
    def __init__(self): ...


class PALETTE:
    RED: int
    PINK: int
    PURPLE: int
    DEEP_PURPLE: int
    INDIGO: int
    BLUE: int
    LIGHT_BLUE: int
    CYAN: int
    TEAL: int
    GREEN: int
    LIGHT_GREEN: int
    LIME: int
    YELLOW: int
    AMBER: int
    ORANGE: int
    DEEP_ORANGE: int
    BROWN: int
    BLUE_GREY: int
    GREY: int
    NONE: int
    def __init__(self): ...


class OPA:
    TRANSP: int
    COVER: int
    def __init__(self): ...


class ANIM:
    OFF: int
    ON: int
    def __init__(self): ...


class STATE:
    DEFAULT: int
    CHECKED: int
    FOCUSED: int
    FOCUS_KEY: int
    EDITED: int
    HOVERED: int
    PRESSED: int
    SCROLLED: int
    DISABLED: int
    USER_1: int
    USER_2: int
    USER_3: int
    USER_4: int
    ANY: int
    def __init__(self): ...


class TEXT_DECOR:
    NONE: int
    UNDERLINE: int
    STRIKETHROUGH: int
    def __init__(self): ...


class lv_event:
    def get_code(self) -> int: ...
    def get_target(self) -> lv_obj: ...


class lv_color_t:
    ...


def lv_color_hex(hex: int64) -> lv_color_t: ...


class lv_timer_t:
    def set_period(period: int): ...
    def set_cb(cb: any): ...
    def _del(self): ...


def palette_lighten(p: int, lvl: int) -> lv_color_t: ...
def palette_main(p: int) -> lv_color_t: ...


class style_t:
    def __init__(self): ...
    def init(self): ...
    def set_width(self, value: int): ...
    def set_min_width(self, value: int): ...
    def set_max_width(self, value: int): ...
    def set_height(self, value: int): ...
    def set_min_height(self, value: int): ...
    def set_max_height(self, value: int): ...
    def set_x(self, value: int): ...
    def set_y(self, value: int): ...
    def set_align(self, value: int): ...
    def set_transform_width(self, value: int): ...
    def set_transform_height(self, value: int): ...
    def set_translate_x(self, value: int): ...
    def set_translate_y(self, value: int): ...
    def set_transform_zoom(self, value: int): ...
    def set_transform_angle(self, value: int): ...
    def set_transform_pivot_x(self, value: int): ...
    def set_transform_pivot_y(self, value: int): ...
    def set_pad_top(self, value: int): ...
    def set_pad_bottom(self, value: int): ...
    def set_pad_left(self, value: int): ...
    def set_pad_right(self, value: int): ...
    def set_pad_row(self, value: int): ...
    def set_pad_column(self, value: int): ...
    def set_bg_color(self, value: lv_color_t): ...
    def set_bg_opa(self, value: int): ...
    def set_bg_grad_color(self, value: lv_color_t): ...
    def set_bg_grad_dir(self, value: int): ...
    def set_bg_main_stop(self, value: int): ...
    def set_bg_grad_stop(self, value: int): ...
    # def set_bg_grad(self, value: lv_grad_dsc_t):...
    def set_bg_dither_mode(self, value: int): ...
    def set_bg_img_src(self, value: bytes): ...
    def set_bg_img_opa(self, value: int): ...
    def set_bg_img_recolor(self, value: lv_color_t): ...
    def set_bg_img_recolor_opa(self, value: int): ...
    def set_bg_img_tiled(self, value: int): ...
    def set_border_color(self, value: lv_color_t): ...
    def set_border_opa(self, value: int): ...
    def set_border_width(self, value: int): ...
    def set_border_side(self, value: int): ...
    def set_border_post(self, value: int): ...
    def set_outline_width(self, value: int): ...
    def set_outline_color(self, value: lv_color_t): ...
    def set_outline_opa(self, value: int): ...
    def set_outline_pad(self, value: int): ...
    def set_shadow_width(self, value: int): ...
    def set_shadow_ofs_x(self, value: int): ...
    def set_shadow_ofs_y(self, value: int): ...
    def set_shadow_spread(self, value: int): ...
    def set_shadow_color(self, value: lv_color_t): ...
    def set_shadow_opa(self, value: int): ...
    def set_img_opa(self, value: int): ...
    def set_img_recolor(self, value: lv_color_t): ...
    def set_img_recolor_opa(self, value: int): ...
    def set_line_width(self, value: int): ...
    def set_line_dash_width(self, value: int): ...
    def set_line_dash_gap(self, value: int): ...
    def set_line_rounded(self, value: int): ...
    def set_line_color(self, value: lv_color_t): ...
    def set_line_opa(self, value: int): ...
    def set_arc_width(self, value: int): ...
    def set_arc_rounded(self, value: int): ...
    def set_arc_color(self, value: lv_color_t): ...
    def set_arc_opa(self, value: int): ...
    def set_arc_img_src(self, value: bytes): ...
    def set_text_color(self, value: lv_color_t): ...
    def set_text_opa(self, value: int): ...
    # def set_text_font(self, value: lv_font_t): ...
    def set_text_letter_space(self, value: int): ...
    def set_text_line_space(self, value: int): ...
    def set_text_decor(self, value: int): ...
    def set_text_align(self, value: int): ...
    def set_radius(self, value: int): ...
    def set_clip_corner(self, value: int): ...
    def set_opa(self, value: int): ...
    # def set_color_filter_dsc(self, value: lv_color_filter_dsc_t): ...
    def set_color_filter_opa(self, value: int): ...
    # def set_anim(self, value: lv_anim_t): ...
    def set_anim_time(self, value: int): ...
    def set_anim_speed(self, value: int): ...
    # def set_transition(self, value: lv_style_transition_dsc_t): ...
    def set_blend_mode(self, value: int): ...
    def set_layout(self, value: int): ...
    def set_base_dir(self, value: int): ...
    def reset(self): ...
    def register_prop(self, flag: int) -> int: ...
    def get_num_custom_props(self) -> int: ...
    def remove_prop(self, prop: int) -> int: ...
    # def set_prop(self, prop: int, value: lv_style_value_t): ...
    # def set_prop_meta(self, prop: int, meta: int): ...
    # def get_prop(self, prop: int, value: lv_style_value_t) -> int: ...
    # def transition_dsc_init(self, tr: lv_style_transition_dsc_t, props: int, path_cb: int, time: int, delay: int, user_data: int): ...
    # def prop_get_default(self, prop: int) -> lv_style_value_t: ...
    def is_empty(self) -> int: ...
    def set_size(self, value: int): ...
    def set_pad_all(self, value: int): ...
    def set_pad_hor(self, value: int): ...
    def set_pad_ver(self, value: int): ...
    def set_pad_gap(self, value: int): ...
    def prop_has_flag(self, prop: int, flag: int) -> int: ...


class lv_obj:
    def __init__(self, parent: lv_obj): ...
    def add_state(self, state: int): ...
    def add_event_cb(self, event_cb: any, filter: int, user_data: pointer): ...
    def add_style(self, style: style_t, selector: int): ...
    def set_pos(self, x: int, y: int): ...
    def set_x(self, x: int): ...
    def set_y(self, y: int): ...
    def set_size(self, w: int, h: int): ...
    def refr_size(self) -> int: ...
    def set_width(self, w: int): ...
    def set_height(self, h: int): ...
    def set_content_width(self, w: int): ...
    def set_content_height(self, h: int): ...
    def set_layout(self, layout: int): ...
    def is_layout_positioned(self) -> int: ...
    def mark_layout_as_dirty(self): ...
    def update_layout(self): ...
    def set_align(self, align: int): ...
    def align(self, align: int, x_ofs: int, y_ofs: int): ...
    def align_to(self, base: lv_obj, align: int, x_ofs: int, y_ofs: int): ...
    def center(self): ...
    # def get_coords(self, coords: lv_area_t): ...
    def get_x(self) -> int: ...
    def get_x2(self) -> int: ...
    def get_y(self) -> int: ...
    def get_y2(self) -> int: ...
    def get_x_aligned(self) -> int: ...
    def get_y_aligned(self) -> int: ...
    def get_width(self) -> int: ...
    def get_height(self) -> int: ...
    def get_content_width(self) -> int: ...
    def get_content_height(self) -> int: ...
    # def get_content_coords(self, area: lv_area_t): ...
    def get_self_width(self) -> int: ...
    def get_self_height(self) -> int: ...
    def refresh_self_size(self) -> int: ...
    def refr_pos(self): ...
    def move_to(self, x: int, y: int): ...
    def move_children_by(self, x_diff: int, y_diff: int, ignore_floating: int): ...

    def transform_point(self, p: point_t, recursive: int, inv: int): ...
    # def get_transformed_area(self, area: lv_area_t, recursive: int, inv: int): ...
    # def invalidate_area(self, area: lv_area_t): ...
    def invalidate(self): ...
    # def area_is_visible(self, area: lv_area_t) -> int: ...
    def is_visible(self) -> int: ...
    def set_ext_click_area(self, size: int): ...
    # def get_click_area(self, area: lv_area_t): ...
    def hit_test(self, point: point_t) -> int: ...


class indev_t:
    def get_vect(self, point: point_t): ...


def obj(parent: lv_obj) -> lv_obj: ...
def indev_get_act() -> indev_t: ...


class point_t:
    def __init__(self): ...


class arc(lv_obj):
    MODE_NORMAL: int
    MODE_SYMMETRICAL: int
    MODE_REVERSE: int
    def __init__(self, parent: lv_obj): ...
    def set_start_angle(self, start: int): ...
    def set_end_angle(self, angle: int): ...
    def set_angles(self, start: int, end: int): ...
    def set_bg_start_angle(self, start: int): ...
    def set_bg_end_angle(self, angle: int): ...
    def set_bg_angles(self, start: int, end: int): ...
    def set_rotation(self, rotation: int): ...
    def set_mode(self, mode: int): ...
    def set_value(self, value: int): ...
    def set_range(self, min: int, max: int): ...
    def set_change_rate(self, rate: int): ...
    def get_angle_start(self) -> int: ...
    def get_angle_end(self) -> int: ...
    def get_bg_angle_start(self) -> int: ...
    def get_bg_angle_end(self) -> int: ...
    def get_value(self) -> int: ...
    def get_min_value(self) -> int: ...
    def get_max_value(self) -> int: ...
    def get_mode(self) -> int: ...
    # def get_rotation(self) -> int: ...


class bar(lv_obj):
    def __init__(self, parent: lv_obj): ...
    def set_value(self, value: int, anim: int): ...
    def set_start_value(self, start_value: int, anim: int): ...
    def set_range(self, min: int, max: int): ...
    def set_mode(self, mode: int): ...
    def get_value(self) -> int: ...
    def get_start_value(self) -> int: ...
    def get_min_value(self) -> int: ...
    def get_max_value(self) -> int: ...
    def get_mode(self) -> int: ...


class btn(lv_obj):
    def __init__(self, parent: lv_obj): ...


class checkbox(lv_obj):
    def __init__(self, parent: lv_obj): ...
    def set_text(self, txt: str): ...
    def set_text_static(self, txt: str): ...
    def get_text(self) -> str: ...


class dropdown(lv_obj):
    def __init__(self, parent: lv_obj): ...
    def set_text(self, txt: str): ...
    def set_options(self, options: str): ...
    def add_option(self, option: str, pos: int): ...
    def clear_options(self): ...
    def set_selected(self, sel_opt: int): ...
    def set_dir(self, dir: int): ...
    def set_symbol(self, symbol: str): ...
    def set_selected_hightlight(self, en: int): ...
    # def get_list(self) -> lv_obj: ...
    def get_text(self) -> str: ...
    def get_options(self) -> str: ...
    def get_selected(self) -> int: ...
    def get_option_cnt(self) -> int: ...
    def get_selected_str(self) -> str: ...
    def get_option_index(self, option: str) -> int: ...
    def get_symbol(self) -> str: ...
    def get_selected_highlight(self) -> int: ...
    def get_dir(self) -> int: ...
    def open(self): ...
    def close(self): ...
    def is_open(self) -> int: ...


class label(lv_obj):
    def __init__(self, parent: lv_obj): ...
    def set_text(self, txt: str): ...
    def set_long_mode(self, mode: int): ...
    def set_recolor(self, en: int): ...
    def set_style_text_align(self, value: int, selector: int): ...


class roller(lv_obj):
    def __init__(self, parent: lv_obj): ...
    def set_options(self, options: str, mode: int): ...
    def set_visible_row_count(self, row_cnt: int): ...


class slider(lv_obj):
    def __init__(self, parent: lv_obj): ...


class switch(lv_obj):
    def __init__(self, parent: lv_obj): ...


class table(lv_obj):
    def __init__(self, parent: lv_obj): ...
    def set_cell_value(self, row: int, col: int, txt: str): ...


class img_dsc_t:
    def __init__(self, dsc_dict: dict): ...


class img(lv_obj):
    def __init__(self, parent: lv_obj): ...
    """
    void lv_img_set_src(lv_obj_t * obj, const void * src);
    void lv_img_set_offset_x(lv_obj_t * obj, lv_coord_t x);
    void lv_img_set_offset_y(lv_obj_t * obj, lv_coord_t y);
    void lv_img_set_angle(lv_obj_t * obj, int16_t angle);
    void lv_img_set_pivot(lv_obj_t * obj, lv_coord_t x, lv_coord_t y);
    void lv_img_set_zoom(lv_obj_t * obj, uint16_t zoom);
    void lv_img_set_antialias(lv_obj_t * obj, bool antialias);
    void lv_img_set_size_mode(lv_obj_t * obj, lv_img_size_mode_t mode);
    const void * lv_img_get_src(lv_obj_t * obj);
    lv_coord_t lv_img_get_offset_x(lv_obj_t * obj);
    lv_coord_t lv_img_get_offset_y(lv_obj_t * obj);
    uint16_t lv_img_get_angle(lv_obj_t * obj);
    void lv_img_get_pivot(lv_obj_t * obj, lv_point_t * pivot);
    uint16_t lv_img_get_zoom(lv_obj_t * obj);
    bool lv_img_get_antialias(lv_obj_t * obj);
    lv_img_size_mode_t lv_img_get_size_mode(lv_obj_t * obj);
    """

    def set_src(self, src: img_dsc_t): ...
    def set_offset_x(self, x: int): ...
    def set_offset_y(self, y: int): ...
    def set_angle(self, angle: int): ...
    def set_pivot(self, x: int, y: int): ...
    def set_zoom(self, zoom: int): ...
    def set_antialias(self, antialias: int): ...
    def set_size_mode(self, mode: int): ...
    def get_src(self) -> img_dsc_t: ...
    def get_offset_x(self) -> int: ...
    def get_offset_y(self) -> int: ...
    def get_angle(self) -> int: ...
    # def get_pivot(self) -> lv_point: ...
    def get_zoom(self) -> int: ...
    def get_antialias(self) -> int: ...
    def get_size_mode(self) -> int: ...


class textarea(lv_obj):
    def __init__(self, parent: lv_obj): ...
    def set_one_line(en: int): ...


def scr_act() -> lv_obj: ...
def timer_create_basic() -> lv_timer_t: ...
