/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Header file for .
*/
#ifndef ACTOR_WOLF_H
    #define ACTOR_WOLF_H
    #define PLAYER_RADIUS 10.0f
    #define PLAYER_BASE_ATK 6
    #include <SDL.h>

typedef struct wolf_context_s bst_context_t;
typedef struct textures_s textures_t;
typedef struct bullet_s bullet_t;
typedef struct blood_s blood_t;
typedef struct player_s player_t;

typedef enum buff_e {
    BUFF_ATK,
    BUFF_HP,
    BUFF_SPD,
    BUFF_ATKSPD,    
    BUFF_AMMO,
} buff_type_t;

typedef struct buff_s {
    buff_type_t type;
    char is_first_time;
    long double value;
    long double duration;  // In milliseconds
    struct buff_s *next;
    struct buff_s *prev;
} buff_t;

void add_buff(buff_t **head, buff_type_t type, long double value,
    long double duration);
void update_buff(bst_context_t *context, player_t *player);
void apply_buff(player_t *player, buff_t *buff);
void remove_buff(buff_t **head, buff_t *buff);
int clear_buffs(buff_t *head);

typedef enum rdi_e {
    DUCKING,
    IDLING,
    WALKING,
    RUNNING,
    EMOTING,
} rdi_t;

typedef enum message_type_s {
    KILL,
    INFO,
    OTHER,
} message_type_t;

/* Parametre of the view for single player */
typedef struct view_param_s {
    int offx;
    int offy;
    int casted_rays;
    float fov;
    sfVector2i size;
} view_param_t;

typedef struct draw_utils_s {
    sfTexture *render_texture;
    sfSprite *render_sprite;
    sfRectangleShape *deadrect;
    sfIntRect self_rect;
    sfIntRect apparance_rect;
} draw_utils_t;

typedef struct game_meta_s {
    double life;
    double maxhp;
    int ammo;
    int max_ammo;
    double atk;
    float atkspd;
    float spd;
    rdi_t rdi;
    int gamepad_is_ducking;
} game_meta_t;

typedef struct voicelines_s {
    sfSound *reload;
    sfSound *midlife;
    sfSound *skill;
    sfSound *shot;
    sfSound *selection;
    sfSound *death;
    sfSound *win;
    sfSound *heal;
} voicelines_t;

typedef struct character_s {
    char *name;
    voicelines_t voicelines;
    textures_t *apparance;
    textures_t *self;
    textures_t *projectile;
    int (*skill)();
    int (*endskill)();
    float skill_cooldown_m;
    float skill_cooldown;
    float endskill_cooldown;
    float maxhp;
    float atk;
    float ammo;
    float cooldown_till_shot;
} character_t;

character_t *get_character(bst_context_t *context, const char *name);
int destroy_characters(character_t **characters, const int n_characters);

typedef struct cooldowns_s {
    float till_reload;
    float till_competence;
    float till_shot;
    float till_respawn;
} cooldowns_t;

// Duration in milliseconds
typedef struct bleeding_s {
    float base_life;
    float target_life;
    float dps;
    float duration;
    float time_elapsed;
} bleeding_t;

void reinit_bleeding(bleeding_t *bleeding);
void add_bleeding_to_player(player_t *player, const float dps,
    const float duration);

typedef struct healing_s {
    float base_life;
    float target_life;
    float hps;
    float duration;
    float time_elapsed;
} healing_t;

void reinit_healing(healing_t *healing);
void add_healing_to_player(player_t *player, const float dps,
    const float duration);

typedef struct messages_s {
    float duration;
    char *text;
    message_type_t type;
    struct messages_s *next;
    struct messages_s *prev;
} messages_t;

int add_message(messages_t **head, const float duration, char *text,
    const message_type_t type);
int count_messages_with_type(messages_t *messages, const message_type_t type);
void delete_all_messages(messages_t *head);
void delete_a_message(messages_t **head, messages_t *message);
void update_messages(player_t *player);
void render_messages(player_t *player);

typedef struct sdl_config_s {
    SDL_GameController *gc;
    SDL_Joystick *js;
    SDL_Haptic *h;
} sdl_config_t;

typedef struct player_s {
    sfBool is_bot;
    sfUint8 *framebuffer;
    double *zbuffer;
    view_param_t param;
    sfClock *clock;
    draw_utils_t *utils;
    float base_angle;
    float base_x;
    float base_y;
    float *angle;
    float *x;
    float *y;
    long double delta_t;
    void (*time)();
    void (*move)();
    int device;
    char *name;
    int equipe;
    char (*move_select)(struct player_s *, int *, int *);
    game_meta_t infos;
    cooldowns_t cooldowns;
    character_t *character;
    struct player_s *killer;
    float hitbox_radius;
    sfVector2i kd;
    int score;

    // Buffs, debuffs, healing, bleeding, ...
    buff_t *buff;
    bleeding_t bleeding;
    healing_t healing;

    int is_endskill_used;
    int is_bleeding_others;
    blood_t *blood;
    voicelines_t voicelines;
    sfBool is_visible;
    int (*skill_reserve)();
    int (*endskill_reserve)();
    int is_left_hand;
    messages_t *messages;
    sdl_config_t sdl;
    dict_t *dict;
} player_t;

void init_sdl(player_t *player);

int init_player_voicelines(player_t *player, bst_context_t *context);

player_t *get_nearest_ally(player_t **players, player_t *player, int i);
player_t *get_nearest_enemy(player_t **players, player_t *player, int i);

int skill_heal(bst_context_t *context, player_t *self);
int skill_heal_end(bst_context_t *context, player_t *self, sfBool force);
int skill_wall(bst_context_t *context, player_t *self);
int skill_wall_end(bst_context_t *context, player_t *self, sfBool force);
int skill_atk(bst_context_t *context, player_t *self);
int skill_atk_end(bst_context_t *context, player_t *self, sfBool force);
int skill_bleeding(bst_context_t *context, player_t *self);
int skill_bleeding_end(bst_context_t *context, player_t *self, sfBool force);
int skill_dash(bst_context_t *context, player_t *self);
int skill_dash_end(bst_context_t *context, player_t *self, sfBool force);
int skill_invisible(bst_context_t *context, player_t *self);
int skill_invisible_end(bst_context_t *context, player_t *self, sfBool force);
int skill_steal(bst_context_t *context, player_t *self);
int skill_steal_end(bst_context_t *context, player_t *self, sfBool force);
int skill_boom(bst_context_t *context, player_t *self);
int skill_boom_end(bst_context_t *context, player_t *self, sfBool force);
int skill_radiance(bst_context_t *context, player_t *self);
int skill_radiance_end(bst_context_t *context, player_t *self, sfBool force);

int create_player(player_t **player, const int i, sfVideoMode v);

int create_players(player_t ***players, const int n_players);
int destroy_players(player_t **players, const int n_players);

void player_timer(player_t *player, bst_context_t *context);

void player_movement_keyboard(bst_context_t *data, player_t *player);
void player_movement_gamepad(bst_context_t *context, player_t *player);

/* AI */
void player_movement_ai(bst_context_t *context, player_t *player);

void reload(player_t *player);
void shot(bst_context_t *context, player_t *player);
int change_rect(player_t *player);

char player_select_keyboard(player_t *player, int *index, int *dindex);
char player_select_gamepad(player_t *player, int *index, int *dindex);

void move_player_to(player_t *player, sfVector2f base_pos,
    sfVector2f target_pos, bst_context_t *context);

int handle_slide_collision_radius(sfVector2f *pos,
    sfVector2f target, bst_context_t *ctx);

void player_resolve_bleeding(player_t *player, bst_context_t *context);
void deal_damage_to_player(bst_context_t *ctx, player_t *dst, player_t *src);

int spawn(player_t *player, bst_context_t *context);

int heal_player(player_t *self, const float ammount);

void interact_sheep(player_t *player, bst_context_t *context);
void fire_sheep(player_t *player, bst_context_t *context);
void defire_sheep(player_t *player, bst_context_t *context);
void eteint_le_noir_mouton(bst_context_t *context);

typedef struct bullet_s {
    player_t *player;
    sfVector2f pos;
    sfVector2f dir;
    int speed;
    struct bullet_s *next;
    struct bullet_s *prev;
    sfClock *clock;
} bullet_t;

void add_bullet(bullet_t **head, player_t *player);
void destroy_bullet(bullet_t **head, bullet_t *self);
void destroy_bullets(bullet_t *head);

void udpdate_bullets(bst_context_t *context);

typedef struct stuffs_s {
    int type;
    sfVector2f pos;
    struct stuffs_s *next;
} stuffs_t;

void destroy_stuffs(stuffs_t *head);
void add_stuff(stuffs_t **head, sfVector2f pos, const int type);

typedef struct blacksheep_s {
    sfClock *clock;
    sfVector2f pos;
    player_t *is_carried;
    player_t *diffusing;
    unsigned char is_fired;
    float firing;
    sfIntRect rect;
    textures_t *texture;
} blacksheep_t;

int destroy_blacksheep(blacksheep_t *blacksheep);
blacksheep_t *create_blacksheep(bst_context_t *context);
int spawn_blacksheep(bst_context_t *context);
void update_blacksheep(bst_context_t *context);

void drop_blacksheep(bst_context_t *context);

#endif /* ACTOR_WOLF_H */
