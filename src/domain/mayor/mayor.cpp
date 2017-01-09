//
// Created by te on 20-Dec-16.
//

#include <random>
#include "mayor.h"

namespace domain{

    mayor::mayor() {

    }

    mayor::mayor(std::string name, std::vector<std::string> hobbies, std::vector<std::string> behavior) :
            m_name(name), m_behavior(behavior), m_hobbies(hobbies){}

    const milestone_group mayor::get_milestone_group(std::string counter_name) {
        if(m_milestone_groups.find(counter_name) != m_milestone_groups.end())
        {
            return m_milestone_groups[counter_name];
        }
        else{
            milestone_group group = domain::milestone_group();
            group.counter_name = "NA";
            return group;
        }
    }

    void mayor::add_milestone_group(milestone_group group) {
        m_milestone_groups[group.counter_name] = group;
    }

    void mayor::add_milestone_groups(std::vector<milestone_group> groups) {
        for(auto group : groups){
            m_milestone_groups[group.counter_name] = group;
        }
    }

    std::string mayor::get_name() const {
        return m_name;
    }

    std::vector<std::string> mayor::get_behavior() const {
        return m_behavior;
    }

    void mayor::set_behavior(std::vector<std::string> behavior) {
        m_behavior = behavior;
    }

    std::vector<std::string> mayor::get_hobbies() const {
        return m_hobbies;
    }

    void mayor::set_hobbies(std::vector<std::string> hobbies) {
        m_hobbies = hobbies;
    }

    void mayor::init(game_level::game_stats* init) {
        reset();
        setup(init);
    }

    void mayor::reset() {
        std::queue<domain::milestone>().swap(m_queue);
    }

    void mayor::setup(game_level::game_stats* init) {
        // set all the init milestones to reached without adding it to queue to avoid a mass amount of milestones in queue
        get_new_reached_milestones(init);
    }

    void mayor::notify(game_level::game_stats *p_observee, std::string title) {
        update(p_observee, title);

        /** EXAMPLE
        mayor ravanna = mayor("Ravanna", {"Playing dictator"}, {"Aggresive", "Conquest orientated"});
        milestone milestone1 = milestone();
        milestone1.min = 4;
        milestone1.max = 4;
        milestone1.responses = {"This is only the beginning my servant."};
        milestone_group group1 = milestone_group();
        group1.display_name = "Buildings";
        group1.counter_name = "buildings";
        group1.milestones = {milestone1};
        ravanna.add_milestone_group(group1);
        */
    }

    void mayor::update(game_level::game_stats *p_observee, std::string title) {
        for(milestone m : get_new_reached_milestones(p_observee, title)){
            m_queue.push(m);
        }
    }

    std::string mayor::get_random_response(milestone milestone) {
        if( milestone.responses.size() == 0){
            return "<milestone has no response text>";
        }
        else{
            std::random_device rd;
            std::mt19937 rnd(rd());
            std::uniform_int_distribution<> response_index(0, milestone.responses.size() - 1);
            return milestone.responses[response_index(rnd)];
        }
    }

    std::vector<milestone> mayor::get_new_reached_milestones(game_level::game_stats* game_stats, std::string counter_name) {

        std::vector<milestone> result = std::vector<milestone>();
        // in case its "" search all
        if(counter_name == ""){
            // search through all the game stats and compare them with the groups to find a intersect
            for(const std::pair<std::string, int>& p : game_stats->get()){
                for(const std::pair<std::string, milestone_group>& group : m_milestone_groups){
                    // intersect exists
                    if(group.first == p.first){
                        // for each milestone check if it is not reached and its between the min and max
                        for(milestone m : group.second.milestones){
                            if(!m.reached && m.min >= p.second && m.max <= p.second){
                                m.reached = true;
                                result.push_back(m);
                            }
                        }
                    }
                }
            }
        }
        else if(m_milestone_groups.find(counter_name) != m_milestone_groups.end() &&
                game_stats->get().find(counter_name) != game_stats->get().end()){

            auto counter = game_stats->get()[counter_name];
            auto group =  m_milestone_groups[counter_name];
            for(milestone m : group.milestones){
                if(!m.reached && m.min >= counter && m.max <= counter){
                    m.reached = true;
                    result.push_back(m);
                }
            }
        }

        return result;
    }

    std::string mayor::get_fifo_milestone_response() {
        if (!m_queue.empty())
        {
            auto r = m_queue.front();
            m_queue.pop();
            return get_random_response(r);
        }
        else{
            return "";
        }
    }


}