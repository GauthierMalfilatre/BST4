##
## EPITECH PROJECT, 2025
## WOLF3D
## File description:
## Makefile for wolf3d project
##

SRC = 	src/main.c \
		\
		src/context/init.c \
		src/context/destroy.c \
		src/context/load_setting.c \
		\
		src/context/view/init.c \
		src/context/view/destroy.c \
		src/context/view/change_resolution.c \
		\
		src/sound/music.c \
		src/sound/sound.c \
		src/sound/play_force.c \
		src/sound/linked/linked.c \
		\
		src/actor/player/messages/messages.c \
		src/actor/player/messages/count.c \
		src/actor/player/destroy.c \
		src/actor/player/init.c \
		src/actor/player/create_player.c \
		src/actor/player/damage.c \
		src/actor/player/heal.c \
		src/actor/player/bleeding.c \
		src/actor/player/select/keypad.c \
		src/actor/player/select/gamepad.c \
		src/actor/player/skills/skill_heal.c \
		src/actor/player/skills/skill_add_wall.c \
		src/actor/player/skills/skill_buff_atk.c \
		src/actor/player/skills/skill_bleed.c \
		src/actor/player/skills/skill_dash.c \
		src/actor/player/skills/skill_invisible.c \
		src/actor/player/skills/skill_steal.c \
		src/actor/player/skills/skill_tp.c \
		src/actor/player/move/spawn.c \
		src/actor/player/move/keypad.c \
		src/actor/player/move/gamepad.c \
		src/actor/player/move/fire_sheep.c \
		src/actor/player/move/interact_sheep.c \
		src/actor/player/move/handle_move.c \
		src/actor/player/move/move_player.c \
		src/actor/player/move/shot.c \
		src/actor/player/move/change_rect.c \
		src/actor/player/time/timer.c \
		src/actor/bullet/linked.c \
		src/actor/bullet/update_bullets.c \
		src/actor/character/destroy.c \
		src/actor/character/get.c \
		src/actor/stuffs/linked.c \
		src/actor/blacksheep/init.c \
		src/actor/blacksheep/destroy.c \
		src/actor/blacksheep/update.c \
		src/actor/blacksheep/drop.c \
		\
		src/scenes/game/sheep_mode/init.c \
		src/scenes/game/sheep_mode/destroy.c \
		src/scenes/game/sheep_mode/event.c \
		src/scenes/game/sheep_mode/timer.c \
		src/scenes/game/sheep_mode/update.c \
		src/scenes/game/sheep_mode/render.c \
		\
		src/scenes/interlude/init.c \
		src/scenes/interlude/destroy.c \
		src/scenes/interlude/event.c \
		src/scenes/interlude/timer.c \
		src/scenes/interlude/update.c \
		src/scenes/interlude/render.c \
		\
		src/scenes/game/hill_mode/init.c \
		src/scenes/game/hill_mode/destroy.c \
		src/scenes/game/hill_mode/event.c \
		src/scenes/game/hill_mode/timer.c \
		src/scenes/game/hill_mode/update.c \
		src/scenes/game/hill_mode/render.c \
		\
		src/parser/parser.c \
		src/parser/wall/add_wall.c \
		src/parser/wall/add_temp_wall.c \
		src/parser/player/add_player.c \
		src/parser/texture/add_texture.c \
		src/parser/character/add_character.c \
		src/parser/maps/add_floor.c \
		src/parser/maps/add_map.c \
		src/parser/maps/add_spawn.c \
		src/parser/maps/add_bsp.c \
		src/parser/maps/add_hp.c \
		src/parser/sound/add_sound.c \
		src/parser/builtins/builtin_require/builtin_require.c \
		src/parser/builtins/builtin_require/check_texture.c \
		src/parser/stuffs/add_stuff.c \
		\
		src/textures/create.c \
		src/textures/destroy.c \
		\
		src/render/raycaster/player_render.c \
		src/render/raycaster/project_on_screen.c \
		src/render/raycaster/actor/bullets/draw_bullets.c \
		src/render/raycaster/actor/blacksheep/draw_blacksheep.c \
		src/render/raycaster/actor/blacksheep/draw_bsp.c \
		src/render/raycaster/actor/stuffs/draw_stuffs.c \
		src/render/raycaster/actor/stuffs/draw_hps.c \
		src/render/raycaster/actor/player/raycaster.c \
		src/render/raycaster/actor/player/draw_wall.c \
		src/render/raycaster/actor/player/draw_player.c \
		src/render/raycaster/actor/player/draw_floor.c \
		src/render/raycaster/actor/player/draw_ceiling.c \
		src/render/raycaster/actor/player/draw_ui.c \
		src/render/raycaster/actor/player/ui/hp.c \
		src/render/raycaster/actor/player/ui/ammo.c \
		src/render/raycaster/actor/player/ui/blacksheep.c \
		src/render/raycaster/actor/player/ui/crosshair.c \
		src/render/raycaster/actor/player/ui/direction.c \
		src/render/raycaster/actor/player/ui/skill.c \
		src/render/raycaster/framebuffer/clear_framebuffer.c \
		src/render/raycaster/framebuffer/draw_rect.c \
		src/render/raycaster/framebuffer/draw_circle.c \
		src/render/raycaster/framebuffer/draw_texture.c \
		src/render/raycaster/framebuffer/draw_texture_cropped.c \
		src/render/raycaster/framebuffer/put_pixel.c \
		src/render/raycaster/framebuffer/blend_color.c \
		src/render/multithread/multithread.c \
		\
		src/utils/get_intersect.c \
		src/utils/get_norme.c \
		src/utils/mouse.c \
		src/utils/update_text.c \
		src/utils/my_lstrcmp.c \
		src/utils/draw_string.c \
		\
		src/scenes/menu/menu.c \
        src/scenes/menu/init_menu.c \
        src/scenes/menu/buttons/menu_draw_buttons.c \
        src/scenes/menu/buttons/menu_init_buttons.c \
        src/scenes/menu/buttons/menu_destroy_buttons.c \
        src/scenes/menu/buttons/menu_buttons_fonction.c \
        src/scenes/menu/buttons/menu_buttons_action.c \
        src/scenes/menu/start_buttons/start_action.c \
        src/scenes/menu/start_buttons/start_draw.c \
        src/scenes/menu/start_buttons/start_fonction.c \
        src/scenes/menu/start_buttons/start_init.c \
        src/scenes/menu/start_buttons/start_destroy.c \
        src/scenes/setting/setting.c \
        src/scenes/setting/init_setting.c \
        src/scenes/setting/shader.c \
        src/scenes/setting/buttons/setting_buttons_fonction.c \
        src/scenes/setting/buttons/setting_destroy_buttons.c \
        src/scenes/setting/buttons/setting_draw_buttons.c \
        src/scenes/setting/buttons/setting_init_buttons.c \
        src/scenes/setting/buttons/setting_buttons_action.c \
        src/scenes/setting/sliders/setting_sliders_fonction.c \
        src/scenes/setting/sliders/setting_draw_sliders.c \
        src/scenes/setting/sliders/setting_init_slider.c \
        src/scenes/setting/sliders/setting_sliders_action.c \
        src/scenes/setting/sliders/setting_destroy_sliders.c \
        src/scenes/setting/sliders/setting_slider_to_percentage.c \
        src/scenes/credit/init_credit.c \
        src/scenes/credit/credit.c \
		src/scenes/selection/buttons/selection_draw_buttons.c \
		src/scenes/selection/buttons/selection_init_buttons.c \
		src/scenes/selection/buttons/setting_buttons_action.c \
		src/scenes/selection/buttons/setting_destroy_buttons.c \
		src/scenes/selection/buttons/selection_buttons_fonction.c \
		src/scenes/selection/selection.c \
		src/scenes/selection/init_selection.c \
		src/scenes/selection/event_selection.c \
		\
		src/maps/create.c \
		src/maps/destroy.c \
		src/maps/remove.c \
		src/maps/linked/spawn_point.c \
		src/maps/linked/bsp.c \
		src/maps/linked/heal_point.c \
		src/maps/linked/temp_wall.c \
		\
		src/team/all.c \
		\
		src/rain/rain.c \
		src/rain/blood.c \
		\
		$(wildcard src/render/raycaster/framebuffer/font/*.c)

CC      = gcc
NAME    ?= wolf3d
SNAME   = vwolf3d
OBJDIR  = build
OBJ     = $(SRC:.c=.o)
OBJ     := $(patsubst src/%, $(OBJDIR)/%, $(OBJ))

LIB     = -Llib/ -lmy
CSFML   = -lcsfml-audio -lcsfml-graphics -lcsfml-window -lcsfml-system -lm
CFLAGS  += -iquote include -Wall -Wextra -O1 -g `sdl2-config --cflags`
LDFLAGS += `sdl2-config --libs`

# COLORS
RED     = \033[0;31m
YELLOW  = \033[0;33m
PURPLE  = \033[0;35m
GRAY1   = \033[0;37m
GRAY2   = \033[0;90m

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C lib/my/ > /dev/null
	@$(CC) -o $(NAME) $(OBJ) $(CSFML) $(LDFLAGS) $(LIB)
	@echo "$(PURPLE)[SUCCESS]:$(GRAY1)\n  |-> Compilation completed!"
	@echo "$(RED)[WARNING!!!]:$(YELLOW)\
		\n  |-> Don't forget to use gdb to launch $(NAME)$(GRAY1)"

exe: all
	@echo "./wolf3d" > $(SNAME)
	@chmod +x $(SNAME)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[COMPILED]:$(GRAY1)\n  |-> [file.c]\
		$(GRAY2)$<\n  |-> [file.o] $(GRAY2) $@"
	@$(CC) -c $< -o $@ $(CFLAGS)

editor:
	@echo "$(PURPLE)[INFO]:$(GRAY1) Building map editor..."
	@$(MAKE) -C bonus/
	@echo "$(PURPLE)[RUN]:$(GRAY1) Launching map_editor"
	@cd bonus && ./map_editor

clean:
	@$(MAKE) -C lib/my clean > /dev/null
	@rm -rf $(OBJDIR)
	@find . -name "*.a" -delete
	@echo "$(RED)[CLEANED]:$(GRAY1)\n  |-> Object files removed!"

fclean: clean
	@rm -f $(NAME) bonus/map_editor $(SNAME)
	@echo "$(RED)[FCLEANED]:$(GRAY1)\n  |-> Binaries removed!"

re: fclean all

size:
	@du -sh --exclude .git --exclude bonus

.PHONY: all clean fclean re editor
