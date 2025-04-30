// custom_status_icons.cpp
// Custom status icons implementation for VIP system

#include "status.hpp"
#include "clif.hpp"
#include "pc.hpp"
#include "battle.hpp"
#include "nullpo.hpp"

// Define custom VIP status icons
// Use values that don't conflict with existing icons
#define SI_VIP_BRONZE 893
#define SI_VIP_SILVER 894
#define SI_VIP_GOLD 895

// Define custom VIP status change types
// Use values that don't conflict with existing types in status.hpp
#define SC_VIP_BRONZE (sc_type)622
#define SC_VIP_SILVER (sc_type)623
#define SC_VIP_GOLD (sc_type)624

// Initialization function to be called at server startup
void custom_status_icons_init(void) {
    ShowInfo("Custom Status Icons for VIP System loaded.\n");
}

// Function to apply VIP status icons
int status_change_start_vip(struct block_list *bl, enum sc_type type, int tid, int val1, int val2, int val3, int val4, int tick, int flag) {
    // Check if this is a VIP status type
    if (type != SC_VIP_BRONZE && type != SC_VIP_SILVER && type != SC_VIP_GOLD)
        return 0; // Not a VIP status, continue with normal processing
        
    struct map_session_data *sd = BL_CAST(BL_PC, bl);
    if (sd == NULL)
        return 0; // Not a player
        
    // Select the appropriate icon based on VIP level
    int icon_id = 0;
    switch (type) {
        case SC_VIP_BRONZE:
            icon_id = SI_VIP_BRONZE;
            break;
        case SC_VIP_SILVER:
            icon_id = SI_VIP_SILVER;
            break;
        case SC_VIP_GOLD:
            icon_id = SI_VIP_GOLD;
            break;
        default:
            return 0;
    }

    // Display the icon above the character
    clif_status_change(bl, icon_id, 1, tick, 0, 0, 0);
    
    // Apply status effect
    sc_start4(bl, bl, type, 100, val1, val2, val3, val4, tick);
    
    return 1; // Successfully handled
}

// Function to remove VIP status icons
int status_change_end_vip(struct block_list *bl, enum sc_type type) {
    // Check if this is a VIP status type
    if (type != SC_VIP_BRONZE && type != SC_VIP_SILVER && type != SC_VIP_GOLD)
        return 0; // Not a VIP status
        
    // Select the appropriate icon based on VIP level
    int icon_id = 0;
    switch (type) {
        case SC_VIP_BRONZE:
            icon_id = SI_VIP_BRONZE;
            break;
        case SC_VIP_SILVER:
            icon_id = SI_VIP_SILVER;
            break;
        case SC_VIP_GOLD:
            icon_id = SI_VIP_GOLD;
            break;
        default:
            return 0;
    }
    
    // Remove the icon from the character
    clif_status_change(bl, icon_id, 0, 0, 0, 0, 0);
    
    return 1;
}
