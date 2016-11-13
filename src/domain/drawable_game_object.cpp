//
// Created by te on 10-Nov-16.
//

#include "drawable_game_object.h"
namespace domain {
    drawable_game_object::drawable_game_object(std::string id, std::string file_loc,
                                               engine::math::vec2_t *image_start_position, int rotation) : id(id),
                                                                                             file_loc(file_loc), rotation(rotation) {
        this->image_start_position = std::unique_ptr<engine::math::vec2_t>(image_start_position);
        this->texture = nullptr;
    }

    void drawable_game_object::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
        load_texture_if_not_loaded_yet(texture_manager);
        draw_object(texture_manager, dest);
    }

    void drawable_game_object::load_texture_if_not_loaded_yet(engine::graphics::texture_manager &texture_manager) {
        // in case texture hasn't been loaded in for this object.
        if (this->texture == nullptr) {
            // look if another object has loaded this specific texture in the texture manager.
            this->texture = texture_manager.find(this->id);
            if (this->texture == nullptr) {
                // in case it didn't then we need to load it in ourselves.
                bool result = texture_manager.load(this->file_loc, this->id);

                // in case the texture is valid then find it again.
                if (result)
                    this->texture = texture_manager.find(this->id);
                else // in case its not loaded in then throw a exception that loading the texture in is impossible.
                    throw std::exception();
            }
        }
    }

    void drawable_game_object::draw_object(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
        texture_manager.draw(this->id, *image_start_position, dest);
    }
}