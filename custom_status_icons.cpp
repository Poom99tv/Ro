// custom_status_icons.cpp
// Custom status icons implementation for VIP system

#include "status.hpp"
#include "clif.hpp"
#include "pc.hpp"
#include "battle.hpp"
#include "nullpo.hpp"
#include "custom_status_icons.hpp"

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
    
    // Display VIP icon in the buff area (right side of the screen)
    // This requires setting the associated status effect ID
    int efst_id = 0;
    switch (type) {
        case SC_VIP_BRONZE:
            efst_id = EFST_VIP_BRONZE;
            break;
        case SC_VIP_SILVER:
            efst_id = EFST_VIP_SILVER;
            break;
        case SC_VIP_GOLD:
            efst_id = EFST_VIP_GOLD;
            break;
    }
    
    // Send packet to display in buff area
    if (efst_id > 0) {
        clif_status_change_single(bl, bl, efst_id, 1, tick, 0);
    }
    
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
    
    // Remove the icon from above the character
    clif_status_change(bl, icon_id, 0, 0, 0, 0, 0);
    
    // Remove VIP icon from the buff area (right side of the screen)
    int efst_id = 0;
    switch (type) {
        case SC_VIP_BRONZE:
            efst_id = EFST_VIP_BRONZE;
            break;
        case SC_VIP_SILVER:
            efst_id = EFST_VIP_SILVER;
            break;
        case SC_VIP_GOLD:
            efst_id = EFST_VIP_GOLD;
            break;
    }
    
    // Send packet to remove from buff area
    if (efst_id > 0) {
        clif_status_change_single(bl, bl, efst_id, 0, 0, 0);
    }
    
    return 1;
}

// Script command to apply VIP status
// Usage: sc_vip <type>, <duration>;
// Type: 1 = Bronze, 2 = Silver, 3 = Gold
// Duration: time in seconds
BUILDIN_FUNC(sc_vip) {
    int type, duration;
    struct map_session_data *sd;
    
    type = script_getnum(st, 2);
    duration = script_getnum(st, 3);
    
    if (!script_rid2sd(sd))
        return SCRIPT_CMD_FAILURE;
        
    enum sc_type sc_type;
    switch(type) {
        case 1: sc_type = SC_VIP_BRONZE; break;
        case 2: sc_type = SC_VIP_SILVER; break;
        case 3: sc_type = SC_VIP_GOLD; break;
        default: return SCRIPT_CMD_FAILURE;
    }
    
    // Apply VIP status
    status_change_start_vip(&sd->bl, sc_type, 10000, 0, 0, 0, 0, duration * 1000, 0);
    
    return SCRIPT_CMD_SUCCESS;
}
