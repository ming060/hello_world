#include<stdio.h>
#include<signal.h>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/agent_callbacks.h>

#define SNMPD_PID_FILE "/run/snmpd.pid"

static int get_snmpd_pid()
{
    int ret = 0;
    int pid = 0;
    FILE *fp;

    fp = fopen(SNMPD_PID_FILE, "r");
    if (fp) {
        ret = fscanf(fp, "%d\n", &pid);
        fclose(fp);
    } else {
        return -1;
    }

    return pid;
}

static int send_signal_to_snmpd(int pid)
{
    int ret = 0;
    ret = kill(pid, SIGHUP);

    if(ret == 0) {
        // TODO change to zlog
        printf("Reconfig snmpd with pid:%d ret=%d\n", pid, ret);
    }
    else {
        // TODO should handle execption
        printf("fail to send SIGHUP signal to snmpd with pid: %d, ret=%d\n", pid, ret);
    }
}

static void reconfig_snmpd()
{
    int ret = 0;
    int pid = 0;

    pid = get_snmpd_pid();

    if(pid > 0) {
        send_signal_to_snmpd(pid);
    }
    else{
        // TODO change to zlog
        printf("fail to get snmpd pid\n");
    }
}

#define COMMUNITY_MAX_LENGTH 30

typedef struct{
    char rocommunity[COMMUNITY_MAX_LENGTH];
    char rwcommunity[COMMUNITY_MAX_LENGTH];
}snmpd_config;

snmpd_config config;

void store_rocommunity_to_snmpd_config(const char *token, char *confline)
{
    printf("token: %s\n", token);
    printf("confline: %s\n", confline);

    strlcpy(config.rocommunity, confline, COMMUNITY_MAX_LENGTH);
}

void store_rwcommunity_to_snmpd_config(const char *token, char *confline)
{
    printf("token: %s\n", token);
    printf("confline: %s\n", confline);
    strlcpy(config.rwcommunity, confline, COMMUNITY_MAX_LENGTH);
}

//#define CONFIG_FILE_PATH "./config/snmpd.conf"
#define CONFIG_FILE_PATH "/home/vagrant/workspace/ming/hello_world/net-snmp_config_manager/config/snmpd.conf"

main()
{
/*
    printf("len: %d\n", strlen(config.rocommunity));

    init_agent("example-demon");
    snmpd_register_config_handler("rocommunity", store_rocommunity_to_snmpd_config, NULL,NULL);
    snmpd_register_config_handler("rwcommunity", store_rwcommunity_to_snmpd_config, NULL, NULL);

    extern struct config_files *config_files;

    read_config(CONFIG_FILE_PATH, config_files->start, 0);
*/

/*
    bzero(&config, sizeof(snmpd_config));

    snprintf(config.rocommunity, COMMUNITY_MAX_LENGTH, "ming_public");
    snprintf(config.rwcommunity, COMMUNITY_MAX_LENGTH, "ming_private");

    FILE *fp;

    fp = fopen(CONFIG_FILE_PATH, "w");
    fprintf(fp, "rocommunity  %s\n", config.rocommunity);
    fprintf(fp, "rwcommunity  %s\n", config.rwcommunity);
    fprintf(fp, "master  agentx\n");
    fclose(fp);
*/
    reconfig_snmpd();

    //remove(CONFIG_FILE_PATH);
}
