/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.67 $ of : mfd-interface.m2c,v $
 *
 * $Id: //BBN_Linux/Branch/Branch_for_SDK_Release_MultiChip_20111013/tclinux_phoenix/apps/public/net-snmp-5.3.1/agent/mibgroup/if-mib/ifXTable/ifXTable_interface.h#1 $
 */
/** @ingroup interface Routines to interface to Net-SNMP
 *
 * \warning This code should not be modified, called directly,
 *          or used to interpret functionality. It is subject to
 *          change at any time.
 * 
 * @{
 */
/*
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 * ***                                                               ***
 * ***  NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE  ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THIS FILE DOES NOT CONTAIN ANY USER EDITABLE CODE.      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THE GENERATED CODE IS INTERNAL IMPLEMENTATION, AND      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***    IS SUBJECT TO CHANGE WITHOUT WARNING IN FUTURE RELEASES.   ***
 * ***                                                               ***
 * ***                                                               ***
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 */
#ifndef IFXTABLE_INTERFACE_H
#define IFXTABLE_INTERFACE_H

#ifdef __cplusplus
extern          "C" {
#endif


#include "ifXTable.h"

    /*
     ********************************************************************
     * Table declarations
     */

    /*
     * PUBLIC interface initialization routine 
     */
    void            _ifXTable_initialize_interface(ifXTable_registration *
                                                   user_ctx, u_long flags);
    void            _ifXTable_shutdown_interface(ifXTable_registration *
                                                 user_ctx);

    ifXTable_registration *ifXTable_registration_get(void);

    ifXTable_registration *ifXTable_registration_set(ifXTable_registration
                                                     * newreg);

    netsnmp_container *ifXTable_container_get(void);
    int             ifXTable_container_size(void);

    u_int           ifXTable_dirty_get(void);
    void            ifXTable_dirty_set(u_int status);

    ifXTable_rowreq_ctx *ifXTable_allocate_rowreq_ctx(void *);
    void            ifXTable_release_rowreq_ctx(ifXTable_rowreq_ctx *
                                                rowreq_ctx);

    int             ifXTable_index_to_oid(netsnmp_index * oid_idx,
                                          ifXTable_mib_index * mib_idx);
    int             ifXTable_index_from_oid(netsnmp_index * oid_idx,
                                            ifXTable_mib_index * mib_idx);

    /*
     *********************************************************************
     * Persistent declarations
     */
    /*
     * persistence
     */
#define LINE_TERM_CHAR '$'

    void            ifXTable_container_init_persistence(netsnmp_container
                                                        *container);
    int             ifXTable_container_should_save(ifXTable_rowreq_ctx *
                                                   rowreq_ctx);


    /*
     * access to certain internals. use with caution!
     */
    void            ifXTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif
#endif                          /* IFXTABLE_INTERFACE_H */
/**  @} */

