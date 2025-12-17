#include "goal_planning.h"
#include <algorithm>
#include <cmath>
#include <sstream>

extern random_device rd;
extern mt19937 rng;

double rn();
int ri(int mx);
double clamp_valence(double v);

map<string, AchievementGoal> GoalPlanner::active_goals_;
vector<string> GoalPlanner::achieved_goals_;

void GoalPlanner::initialize() {
    active_goals_.clear();
    achieved_goals_.clear();
}

AchievementGoal GoalPlanner::formulate_goal_from_context(const string& context, double current_valence) {
    AchievementGoal goal;
    goal.goal_id = generate_goal_id();
    goal.description = "explore and learn about " + context;
    goal.priority = 0.5 + (rn() * 0.5);
    goal.current_progress = 0.0;
    goal.valence_alignment = current_valence;
    goal.expected_completion_value = 0.7;
    
    goal.action_plan = plan_goal_achievement(goal);
    
    active_goals_[goal.goal_id] = goal;
    return goal;
}

vector<PlanStep> GoalPlanner::plan_goal_achievement(const AchievementGoal& goal) {
    vector<PlanStep> plan;
    
    vector<string> actions = {
        "gather_information",
        "analyze_concepts",
        "form_associations",
        "update_valence",
        "consolidate_learning",
        "reflect_on_progress"
    };
    
    for (size_t i = 0; i < actions.size(); ++i) {
        PlanStep step;
        step.action = actions[i];
        step.step_order = i;
        step.expected_outcome = (i + 1.0) / actions.size();
        step.valence_impact = calculate_valence_impact(step.action);
        plan.push_back(step);
    }
    
    return plan;
}

void GoalPlanner::update_goal_progress(const string& goal_id, double progress_delta) {
    if (active_goals_.count(goal_id)) {
        active_goals_[goal_id].current_progress += progress_delta;
        active_goals_[goal_id].current_progress = clamp_valence(active_goals_[goal_id].current_progress);
        
        if (active_goals_[goal_id].current_progress >= 0.95) {
            achieved_goals_.push_back(goal_id);
            active_goals_.erase(goal_id);
        }
    }
}

double GoalPlanner::evaluate_goal_alignment(const AchievementGoal& goal, double current_valence) {
    double alignment = 1.0 - abs(goal.valence_alignment - current_valence);
    alignment *= goal.priority;
    alignment *= (1.0 - goal.current_progress * 0.5);
    
    return clamp_valence(alignment);
}

string GoalPlanner::recommend_next_action(const AchievementGoal& goal) {
    if (goal.action_plan.empty()) {
        return "continue_exploring";
    }
    
    int next_step_idx = min((int)(goal.current_progress * goal.action_plan.size()), 
                            (int)goal.action_plan.size() - 1);
    
    return goal.action_plan[next_step_idx].action;
}

void GoalPlanner::consolidate_achieved_goals() {
    if (achieved_goals_.size() > 100) {
        achieved_goals_.erase(achieved_goals_.begin(), achieved_goals_.begin() + 50);
    }
}

int GoalPlanner::get_active_goal_count() {
    return active_goals_.size();
}

AchievementGoal GoalPlanner::get_highest_priority_goal() {
    AchievementGoal highest;
    double max_priority = -1.0;
    
    for (auto& [id, goal] : active_goals_) {
        double effective_priority = goal.priority * (1.0 - goal.current_progress);
        if (effective_priority > max_priority) {
            max_priority = effective_priority;
            highest = goal;
        }
    }
    
    return highest;
}

string GoalPlanner::generate_goal_id() {
    static int counter = 0;
    return "goal_" + to_string(counter++);
}

double GoalPlanner::calculate_valence_impact(const string& action) {
    if (action == "gather_information") return 0.2;
    if (action == "analyze_concepts") return 0.15;
    if (action == "form_associations") return 0.25;
    if (action == "update_valence") return 0.3;
    if (action == "consolidate_learning") return 0.35;
    if (action == "reflect_on_progress") return 0.4;
    return 0.2;
}
