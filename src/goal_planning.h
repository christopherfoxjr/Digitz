#pragma once
#ifndef GOAL_PLANNING_H
#define GOAL_PLANNING_H

#include <string>
#include <vector>
#include <map>

struct PlanStep {
    std::string action;
    double expected_outcome;
    double valence_impact;
    int step_order;
};

struct AchievementGoal {
    std::string goal_id;
    std::string description;
    double priority;
    double current_progress;
    double valence_alignment;
    std::vector<PlanStep> action_plan;
    double expected_completion_value;
};

class GoalPlanner {
public:
    static void initialize();
    
    static AchievementGoal formulate_goal_from_context(const std::string& context, double current_valence);
    
    static std::vector<PlanStep> plan_goal_achievement(const AchievementGoal& goal);
    
    static void update_goal_progress(const std::string& goal_id, double progress_delta);
    
    static double evaluate_goal_alignment(const AchievementGoal& goal, double current_valence);
    
    static std::string recommend_next_action(const AchievementGoal& goal);
    
    static void consolidate_achieved_goals();
    
    static int get_active_goal_count();
    
    static AchievementGoal get_highest_priority_goal();
    
private:
    static std::map<std::string, AchievementGoal> active_goals_;
    static std::vector<std::string> achieved_goals_;
    
    static std::string generate_goal_id();
    
    static double calculate_valence_impact(const std::string& action);
};

#endif // GOAL_PLANNING_H
