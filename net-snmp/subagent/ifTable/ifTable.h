/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */
#ifndef IFTABLE_H
#define IFTABLE_H

/* function declarations */
void init_ifTable(void);
void initialize_table_ifTable(void);
Netsnmp_Node_Handler ifTable_handler;
Netsnmp_First_Data_Point  ifTable_get_first_data_point;
Netsnmp_Next_Data_Point   ifTable_get_next_data_point;

/* column number definitions for table ifTable */
       #define COLUMN_IFINDEX		1
       #define COLUMN_IFDESCR		2
       #define COLUMN_IFTYPE		3
       #define COLUMN_IFMTU		4
       #define COLUMN_IFSPEED		5
       #define COLUMN_IFPHYSADDRESS		6
       #define COLUMN_IFADMINSTATUS		7
       #define COLUMN_IFOPERSTATUS		8
       #define COLUMN_IFLASTCHANGE		9
       #define COLUMN_IFINOCTETS		10
       #define COLUMN_IFINUCASTPKTS		11
       #define COLUMN_IFINNUCASTPKTS		12
       #define COLUMN_IFINDISCARDS		13
       #define COLUMN_IFINERRORS		14
       #define COLUMN_IFINUNKNOWNPROTOS		15
       #define COLUMN_IFOUTOCTETS		16
       #define COLUMN_IFOUTUCASTPKTS		17
       #define COLUMN_IFOUTNUCASTPKTS		18
       #define COLUMN_IFOUTDISCARDS		19
       #define COLUMN_IFOUTERRORS		20
       #define COLUMN_IFOUTQLEN		21
       #define COLUMN_IFSPECIFIC		22
#endif /* IFTABLE_H */
