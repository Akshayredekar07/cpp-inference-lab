/**
 * ENUMS IN C - Real-World & DSA-Oriented Examples
 *
 * Key Points about enums:
 * - enum is a user-defined type for named integer constants
 * - Makes state, configuration, and modes more readable in production code
 * - Commonly used for: job status, error codes, feature flags, algorithm choice
 * - By default, values start from 0 and increase by 1, but you can assign custom values
 * - enums are NOT strings — they are integers!
 */

#include <stdio.h>

// =============================================
// 1. Basic Enum - Scheduling days (e.g., cron-like)
// =============================================
 enum Days {
     SUNDAY,    // 0
     MONDAY,    // 1
     TUESDAY,   // 2
     WEDNESDAY, // 3
     THURSDAY,  // 4
     FRIDAY,    // 5
     SATURDAY   // 6
 };
 
void basic_enum_demo() {
    printf("=== 1. Basic Enum (Scheduling Days) ===\n");
    
    enum Days backup_day = SUNDAY;
    enum Days deploy_day = THURSDAY;
    
    printf("Backup runs on day number : %d\n", backup_day);   // 0
    printf("Deploy runs on day number : %d\n", deploy_day);  // 4
    printf("Sunday    = %d\n", SUNDAY);
    printf("Monday    = %d\n", MONDAY);
    printf("Wednesday = %d\n", WEDNESDAY);
    printf("Saturday  = %d\n\n", SATURDAY);
    
    if (deploy_day == THURSDAY) {
        printf("Deploy is scheduled correctly before Friday traffic spike.\n\n");
    }
}
 
 // =============================================
// 2. Enum with Custom Values (Job status & error codes)
// =============================================
enum Status {
    JOB_QUEUED    = 0,
    JOB_RUNNING   = 1,
    JOB_COMPLETED = 2,
    JOB_FAILED    = 3
};

enum ErrorCode {
    SUCCESS           = 0,
    FILE_NOT_FOUND    = -1,
    PERMISSION_DENIED = -2,
    OUT_OF_MEMORY     = -3,
    NETWORK_TIMEOUT   = -4
};

// Simulate a file read in a data-processing pipeline
enum ErrorCode read_config_file(const char *path) {
    // In real production code you would use fopen/fread etc.
    // Here we just simulate a failure/success based on the path.
    if (path == NULL) {
        return OUT_OF_MEMORY;
    }
    if (path[0] == '\0') {
        return FILE_NOT_FOUND;
    }
    // Pretend files under "/secure" require extra permission
    if (path[0] == '/' && path[1] == 's') {
        return PERMISSION_DENIED;
    }
    return SUCCESS;
}

void custom_values_demo() {
    printf("=== 2. Job Status & Error Codes (Real-World) ===\n");
    
    enum Status job_status = JOB_QUEUED;
    printf("Initial job status: %d (QUEUED)\n", job_status);
    
    job_status = JOB_RUNNING;
    printf("Job status updated: %d (RUNNING)\n", job_status);
    
    enum ErrorCode cfg_err = read_config_file("/secure/config.json");
    printf("Config load error code: %d\n", cfg_err);
    
    if (cfg_err == SUCCESS) {
        job_status = JOB_COMPLETED;
        printf("Job status updated: %d (COMPLETED)\n\n", job_status);
    } else {
        job_status = JOB_FAILED;
        printf("Job status updated: %d (FAILED)\n\n", job_status);
    }
}
 
 // =============================================
// 3. Enum as Bit Flags (Permissions for a data structure service)
// =============================================
enum Permissions {
    PERM_READ   = 1,        // 001
    PERM_WRITE  = 2,        // 010
    PERM_EXEC   = 4,        // 100
    PERM_RW     = PERM_READ | PERM_WRITE,           // 3
    PERM_RX     = PERM_READ | PERM_EXEC,            // 5
    PERM_RWX    = PERM_READ | PERM_WRITE | PERM_EXEC // 7
};

void mixed_enum_demo() {
    printf("=== 3. Permissions as Bit Flags (Real-World) ===\n");
    
    printf("PERM_READ  = %d\n", PERM_READ);
    printf("PERM_WRITE = %d\n", PERM_WRITE);
    printf("PERM_EXEC  = %d\n", PERM_EXEC);
    printf("PERM_RW    = %d\n", PERM_RW);
    printf("PERM_RX    = %d\n", PERM_RX);
    printf("PERM_RWX   = %d\n\n", PERM_RWX);
    
    int user_perm = PERM_READ | PERM_EXEC;  // e.g., read + execute
    printf("User permissions mask = %d\n", user_perm);
    
    if (user_perm & PERM_WRITE) {
        printf("User CAN write\n");
    } else {
        printf("User CANNOT write\n");
    }
    
    if ((user_perm & PERM_RWX) == PERM_RWX) {
        printf("User has full RWX access\n\n");
    } else {
        printf("User does NOT have full RWX access\n\n");
    }
}
 
 // =============================================
// 4. Practical DSA-like Example: Choosing an algorithm
// =============================================
enum Algorithm {
    ALG_BFS = 1,
    ALG_DFS,
    ALG_DIJKSTRA,
    ALG_QUICKSORT,
    ALG_EXIT
};

void run_algorithm(enum Algorithm algo) {
    switch (algo) {
        case ALG_BFS:
            printf("Running BFS on graph (good for shortest path in unweighted graphs).\n");
            break;
        case ALG_DFS:
            printf("Running DFS (useful for cycle detection, topological sort, etc.).\n");
            break;
        case ALG_DIJKSTRA:
            printf("Running Dijkstra's algorithm for weighted shortest paths.\n");
            break;
        case ALG_QUICKSORT:
            printf("Running Quicksort on incoming request batch.\n");
            break;
        case ALG_EXIT:
            printf("Exiting algorithm selection.\n");
            break;
        default:
            printf("Unknown algorithm selection.\n");
            break;
    }
}

void menu_system_demo() {
    printf("=== 4. Practical Example: Algorithm Selection Menu ===\n");
    
    int choice;
    
    printf("Select algorithm for processing data structure:\n");
    printf("1. BFS (Breadth-First Search)\n");
    printf("2. DFS (Depth-First Search)\n");
    printf("3. Dijkstra (Shortest Path)\n");
    printf("4. Quicksort (Sorting keys)\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    
    // For demo, we set choice manually (in real program use scanf)
    choice = 3;
    printf("%d\n", choice);
    
    run_algorithm((enum Algorithm)choice);
    printf("\n");
}
 
 // =============================================
// 5. Size of Enum
// =============================================
void enum_size_demo() {
    printf("=== 5. Size of Enum Variables ===\n");
    
    printf("Size of enum Days      : %zu bytes\n", sizeof(enum Days));
    printf("Size of enum Status    : %zu bytes\n", sizeof(enum Status));
    printf("Size of enum Permissions: %zu bytes\n", sizeof(enum Permissions));
    printf("(Usually same as int on most platforms)\n");
}
 
 // =============================================
 // MAIN FUNCTION
 // =============================================
 int main() {
     printf("ENUMS IN C - Proper & Complete Example\n");
     printf("======================================\n\n");
 
     basic_enum_demo();
     custom_values_demo();
     mixed_enum_demo();
     menu_system_demo();
     enum_size_demo();
 
     printf("\nKey Takeaways:\n");
     printf("- Use enums instead of magic numbers\n");
     printf("- Makes code readable and less error-prone\n");
     printf("- Can assign custom values or use bit flags\n");
     printf("- Always prefer enum over #define for constants\n");
 
     return 0;
 }