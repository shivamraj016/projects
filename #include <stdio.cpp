#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// --- Configuration ---
#define DATA_POINTS 24
#define PEAK_THRESHOLD 150.0 
#define SHED_AMOUNT 20.0 

// Structure to hold our time-series data and features (Phase 3.1)
typedef struct {
    int hour;             // Feature: Hour of the day (0-23)
    double demand_mw;     // Raw data: Energy consumption
    double load_shifted;  // Optimization result
} EnergyData;

// --- Function 1: Feature Extraction & Data Loading (Phase 3.1 Concept) ---
void load_and_extract_features(EnergyData data[]) {
    // Mock 24-hour demand profile (similar to the peak-heavy profile in the Python example)
    double mock_demand[DATA_POINTS] = {
        100, 90, 80, 70, 75, 85, 110, 130, 150, 160, 155, 140, 
        135, 130, 140, 150, 170, 180, 160, 140, 120, 110, 105, 100
    };

    printf("--- Data Loading and Feature Extraction (24 Hours) ---\n");
    for (int i = 0; i < DATA_POINTS; i++) {
        // Feature Engineering: The hour of the day is our feature
        data[i].hour = i;
        // Data Loading: Mock consumption data
        data[i].demand_mw = mock_demand[i];
        // Initialize load shifted result
        data[i].load_shifted = 0.0; 
        
        printf("Hour %02d: Initial Demand = %.2f MW\n", data[i].hour, data[i].demand_mw);
    }
    printf("------------------------------------------------------\n\n");
}

// --- Function 2: Static Optimization/Control Loop (Problem Statement) ---
// This simulates the 'static schedules or simple control loops' that the project aims to improve.
void apply_static_optimization(EnergyData data[]) {
    printf("--- Applying Static Rule-Based Load Shedding (Optimization) ---\n");
    printf("Rule: If Demand > %.2f MW, shed %.2f MW.\n\n", PEAK_THRESHOLD, SHED_AMOUNT);
    
    for (int i = 0; i < DATA_POINTS; i++) {
        double current_demand = data[i].demand_mw;
        double new_load = current_demand;
        double shed_applied = 0.0;
        
        // Static Control Logic
        if (current_demand > PEAK_THRESHOLD) {
            shed_applied = SHED_AMOUNT;
            new_load = current_demand - shed_applied;
        }
        
        // Store the result
        data[i].load_shifted = new_load;

        printf("Hour %02d: Demand=%.2f MW", data[i].hour, current_demand);
        if (shed_applied > 0) {
            printf(" | ACTION: SHED %.2f MW | New Load=%.2f MW\n", shed_applied, new_load);
        } else {
            printf(" | ACTION: HOLD            | New Load=%.2f MW\n", new_load);
        }
    }
    printf("------------------------------------------------------\n\n");
}

// --- Main Program ---
int main() {
    EnergyData hourly_data[DATA_POINTS];
    double max_original_peak = 0.0;
    double max_optimized_peak = 0.0;

    // Phase 1: Data and Feature Prep
    load_and_extract_features(hourly_data);

    // Phase 2: Static Optimization/Control Loop
    // (In the real project, the ML/RL models would replace this static logic)
    apply_static_optimization(hourly_data);

    // Phase 3: Analysis
    printf("--- Optimization Results Summary ---\n");
    for (int i = 0; i < DATA_POINTS; i++) {
        if (hourly_data[i].demand_mw > max_original_peak) {
            max_original_peak = hourly_data[i].demand_mw;
        }
        if (hourly_data[i].load_shifted > max_optimized_peak) {
            max_optimized_peak = hourly_data[i].load_shifted;
        }
    }

    printf("Original Peak Demand: %.2f MW\n", max_original_peak);
    printf("Optimized Peak Demand: %.2f MW\n", max_optimized_peak);
    printf("\n✅ Peak Reduction Achieved: %.2f MW\n", max_original_peak - max_optimized_peak);
    printf("------------------------------------\n");
    
    // To compile and run this code:
    // 1. Save it as a file (e.g., energy_sim.c)
    // 2. Compile: gcc energy_sim.c -o energy_sim -lm
    // 3. Run: ./energy_sim

    return 0;
}