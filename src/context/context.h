/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for the wolf3d project.
*/
#ifndef CONTEXT_WOLF_3D_H
    #define CONTEXT_WOLF_3D_H

    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include "../actor/actor.h"
    #include "../textures/textures.h"
    #include "../rain/rain.h"

    #define W_FRAMERATE 0
    #define W_SOUND 1
    #define W_MUSIC 2
    #define W_SENSIBILITE 3
    #define W_FULLSCREEN 4
    #define W_NB_PLAYER 5

    #define MENU_MUSIC "./assets/menu_assets/bst.mp3"

    #define SELF_SCENE (context->scenes[context->current_scene])
    #define SELF_MAKE(function) (SELF_SCENE->function(SELF_SCENE, context))

typedef struct button_s button_t;

typedef struct render_manager_s render_manager_t;

// Scene Struct
typedef struct menu_s menu_t;
typedef struct setting_s setting_t;
typedef struct credit_s credit_t;
typedef struct selection_s selection_t;
typedef struct maps_s maps_t;

typedef enum mode_e {
    BS_GO,
    HILL,
} modee_t;

typedef struct bst_s {
    sfClock *clock;
    float timelimit;
    sfRectangleShape *score_rect;
    sfRectangleShape *bar_rect;
    float scale_ratio;
    sfBool is_temp_wall;
    sfFont *font;
    sfText *text;
    rain_t *rain;
} bst_t;

/* Game king of the hill scene */
typedef struct hill_s {
    sfClock *clock;
    float timelimit;
    sfRectangleShape *score_rect;
    sfRectangleShape *bar_rect;
    float scale_ratio;
    sfFont *font;
    sfText *text;
    rain_t *rain;
} hill_t;

typedef struct interlude_s {
    sfSprite *sprite;
    sfText *text;
    sfRectangleShape *rect;
    sfClock *clock;
    sfFont *font;
} interlude_t;

/* Wall struct */
typedef struct wall_s {
    int is_breakable;
    int type;
    float alpha;
    sfVector2f a;
    sfVector2f b;
    player_t *builder;
} wall_t;

/* View (window parameters) */
typedef struct view_s {
    sfRenderWindow *window;
    sfVideoMode videomode;
    sfVector2u win_size;
    float window_diagonal;
    sfCursor *cursor_hand;
    sfCursor *cursor_arrow;
    sfFloatRect *viewports;
} view_t;

typedef struct sounds_s {
    char *name;
    sfSoundBuffer *soundbuffer;
    sfSound *sound;
    struct sounds_s *next;
} sounds_t;

typedef struct {
    sfSound *sound_click;
    sfSoundBuffer *buffer_click;
    sfMusic *music;
    sounds_t *sounds;
} sound_t;

int create_view(view_t **view, unsigned int fullscreen);
void destroy_view(view_t *view);

/* Struct for main games */
typedef struct wolf_context_s {
    view_t *view;
    sfEvent evt;
    textures_t *textures;
    sound_t w_sound;
    unsigned int current_scene;
    menu_t *menu;
    setting_t *setting;
    credit_t *credit;
    selection_t *selection;
    bst_t *bst;
    interlude_t *interlude;
    hill_t *hill;
    unsigned int w_setting[5];
    int n_players;
    player_t **players;
    int n_chars;
    character_t **characters;
    int is_alt;
    maps_t *cmap;
    int n_map;
    maps_t **maps;
    modee_t mode;
    blacksheep_t *bs;
    render_manager_t *render_manager;
    sfVector2i wins;
    int team_winner;
} wolf_context_t;

int create_context(wolf_context_t **context, const char *config_file);
void destroy_context(wolf_context_t *context);
void change_scene(int new_scene, wolf_context_t *window);
void change_resolution(wolf_context_t *window, unsigned int width,
    unsigned int height);

char load_settings(wolf_context_t *context);

int menu_init(wolf_context_t *window);
void menu_update(wolf_context_t *window);
void menu_event(wolf_context_t *window);
void menu_draw(wolf_context_t *window);
void menu_destroy(wolf_context_t *window);

int setting_init(wolf_context_t *window);
void setting_update(wolf_context_t *window);
void setting_event(wolf_context_t *window);
void setting_draw(wolf_context_t *window);
void setting_destroy(wolf_context_t *window);

//Credit management
int credit_init(wolf_context_t *window);
void credit_update(wolf_context_t *window);
void credit_event(wolf_context_t *window);
void credit_draw(wolf_context_t *window);
void credit_destroy(wolf_context_t *window);

int bst_init(wolf_context_t *context);
void bst_update(wolf_context_t *context);
void bst_event(wolf_context_t *context);
void bst_draw(wolf_context_t *context);
void bst_destroy(wolf_context_t *context);

int hill_init(wolf_context_t *context);
void hill_update(wolf_context_t *context);
void hill_event(wolf_context_t *context);
void hill_draw(wolf_context_t *context);
void hill_destroy(wolf_context_t *context);

int selection_init(wolf_context_t *window);
void selection_update(wolf_context_t *window);
void selection_event(wolf_context_t *window);
void selection_draw(wolf_context_t *window);
void selection_destroy(wolf_context_t *window);

int interlude_init(wolf_context_t *context);
void interlude_update(wolf_context_t *context);
void interlude_event(wolf_context_t *context);
void interlude_draw(wolf_context_t *context);
void interlude_destroy(wolf_context_t *context);

#endif /* CONTEXT_WOLF_3D_H */
