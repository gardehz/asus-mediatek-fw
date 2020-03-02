/*
 *  Boa, an http server
 *  Copyright (C) 1995 Paul Phillips <paulp@go2net.com>
 *  Some changes Copyright (C) 1996-99 Larry Doolittle <ldoolitt@jlab.org>
 *  Some changes Copyright (C) 1997-99 Jon Nelson <jnelson@boa.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 1, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/* $Id: //BBN_Linux/Branch/Branch_for_SDK_Release_MultiChip_20111013/tclinux_phoenix/apps/public/boa-asp/src/boa.h#3 $*/

#ifndef _BOA_H
#define _BOA_H

#include <errno.h>
#include <stdlib.h>             /* malloc, free, etc. */
#include <stdio.h>              /* stdin, stdout, stderr */
#include <string.h>             /* strdup */
#include <ctype.h>
#include <time.h>               /* localtime, time */
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>             /* OPEN_MAX */
#include <setjmp.h>

#include <netdb.h>
#include <netinet/in.h>

#include <sys/mman.h>
#include <sys/select.h>
#include <sys/types.h>          /* socket, bind, accept */
#include <sys/socket.h>         /* socket, bind, accept, setsockopt, */
#include <sys/stat.h>           /* open */

#include "compat.h"             /* oh what fun is porting */
#include "defines.h"
#include "globals.h"

#if  defined(TCSUPPORT_WEBSERVER_SSL)
#include <mssl.h>
#endif 
#include <arpa/inet.h>
#include <tcapi.h>
/*------------------------lee------------------------*/ 
//DEBUG
#if 0
#define FASCIST_LOGGING
#define VERY_FASCIST_LOGGING
#define FASCIST_LOGGING1
#define VERY_FASCIST_LOGGING2
#endif
#define ORIGINAL_BEHAVIOR
/*---------------------------------------------------*/
/* define area start*/
#if !defined(TCSUPPORT_C1_NEW_GUI) 
#define PAGEMAP_I_NUM                                    8
#define PAGEMAP_J_NUM                                   9
#endif

#if  defined(TCSUPPORT_CD_NEW_GUI) || defined(TCSUPPORT_FW_UPGRADE_16M)
#if !defined(TCSUPPORT_REDIRECT_WITH_PORTMASK)
#define IP_SKB_MARK 50	
#define SSID2_PORT_MASK 6
#endif
#define SSID1_PORT_MASK 5
#define SSID3_PORT_MASK 7
#define SSID4_PORT_MASK 8
#endif

#ifdef INET6
#define LEFT_SQUARE_BRACKET	"://["
#define RIGHT_SQUARE_BRACKET	"]"
#define IP_TYPE_V4	0
#define IP_TYPE_V6	1
#endif

#if defined(TCSUPPORT_WEB_SAVE)
#define SYSTEM_NODE	"System_Entry"
#define REBOOT_TYPE	"reboot_type"
#define NO_BOOT		0
#endif 
struct pageset {
	char *page_name;
	struct pageset *next;
};

typedef struct param_s {
	char	*name;
	char	*value;
} s_param;

#ifdef ASUS_LOGIN_SESSION	//Andy Chiu, 2015/11/27.
#define DEFAULT_LOGIN_MAX_NUM   5
//asus token status for APP
#define NOTOKEN		1
#define AUTHFAIL	2
#define ACCOUNTFAIL	3
#define NOREFERER	4
#define WEB_NOREFERER	5
#define REFERERFAIL	6
#define LOGINLOCK	7
#define ISLOGOUT	8
#define NOLOGIN		9

#define ASUS_TOKEN_LEN	32

//Andy Chiu, 2016/02/25. Use a link list to record the tokens for clients.
typedef enum CLIENT_TYPE_T
{
	CLI_TYPE_BROWSER = 0,
	CLI_TYPE_APP,
	CLI_TYPE_ATE,
	CLI_TYPE_ASSIA,
	CLI_TYPE_IFTTT
}CLIENT_TYPE;

typedef struct asus_token_table asus_token_t;
struct asus_token_table
{
	CLIENT_TYPE client_type;
	char token[ASUS_TOKEN_LEN];
	char ipaddr[16];
	long login_timestamp;	//time stamp as login success	
	asus_token_t *next;
};
extern asus_token_t *token_head;

//These variables are used to handle the login failed case. 
//When user tried to login more than MAX_LOGIN_FAIL_NUM times in one minute, boa must return LOGINLOCK as error code.
typedef struct login_retry login_retry_t;
struct login_retry
{
	long last_login_timestamp;		//last login time stamp
	int try_num;	//the counter of trying to do login in one minute.
	int is_lock;	//0: unlock, 1:locked
	int err_status;
#ifdef USE_RETRY_LIST
	char ipaddr[16];
	login_retry_t *next;
#endif
};
#ifdef USE_RETRY_LIST
extern login_retry_t * retry_head;
#else
extern login_retry_t retry_flag, retry_flag_wan;
#endif
#define MAX_LOGIN_BLOCK_TIME	300
/* Get Login Token - New add Remaing Lock Time */
extern time_t login_dt;

//The attribute "login_ip_tmp" in the node "WebCurSet_Entry" is ONLY for the user login via browser.

#define ASUSROUTER_TAG	"asusrouter"
#define ASUSROUTER_APP	"DUTUtil"
#define ASUSROUTER_ATE	"ATE"
#define ASUSROUTER_ASSIA "ASSIA"
#define ASUSROUTER_IFTTT "IFTTT"

//#define BOA_DEBUG	1

#define APP_LOGOUT_TIME 6000

char *generate_token(char *token, int len);
int http_login_header(const char *token, request *req, const CLIENT_TYPE cli_type);
void send_r_redirect_page(request *req, const int with_token);
void dbgprintf (const char * format, ...);

CLIENT_TYPE check_client_type(const char *user_agent);
void rm_token_in_list(const char *ipaddr, const char *token, const int timeout);
#define RM_TOKEN_ITEM_BY_IP(ipaddr)	rm_token_in_list(ipaddr, NULL, 0)
#define RM_TOKEN_ITEM_BY_TOKEN(token)	rm_token_in_list(NULL, token, 0)
#define RM_TOKEN_ITEM_BY_TIMEOUT()	rm_token_in_list(NULL, NULL, 1)

asus_token_t* search_token_list(const char *token, const char *ipaddr, CLIENT_TYPE cli_type);
#define SEARCH_TOKEN_LST_BY_TOKEN(token)	search_token_list(token, NULL, -1)
#define SEARCH_TOKEN_LST_BY_IP(ipaddr)	search_token_list(NULL, ipaddr, -1)
#define SEARCH_TOKEN_LST_BY_CLITYPE(type)	search_token_list(NULL, NULL, type)

#ifdef USE_RETRY_LIST
login_retry_t* add_login_retry(const char *ipaddr);
login_retry_t* search_retry_list(const char *ipaddr);
void rm_retry_in_list(const char *ipaddr);
void dump_retry(login_retry_t *retry);
#endif
void dump_token(asus_token_t *token);

#endif

/* alias */
void add_alias(char *fakename, char *realname, int script);
int translate_uri(request * req);
int init_script_alias(request * req, alias * current, int uri_len);
void dump_alias(void);

/* config */
void read_config_files(void);

/* escape */
#include "escape.h"

/* get */

#ifdef TRENDCHIP
#define FAIL_SESSION_TIMEOUT 2
#endif

int init_get(request * req);
int process_get(request * req);
int get_dir(request * req, struct stat *statbuf);

/* hash */
unsigned get_mime_hash_value(char *extension);
char *get_mime_type(char *filename);
char *get_home_dir(char *name);
void dump_mime(void);
void dump_passwd(void);
void show_hash_stats(void);

/* log */
void open_logs(void);
void close_access_log(void);
void log_access(request * req);
void log_error_doc(request * req);
void boa_perror(request * req, char *message);
void log_error_time(void);
void log_error_mesg(char *file, int line, char *mesg);

/* queue */
void block_request(request * req);
void ready_request(request * req);
void dequeue(request ** head, request * req);
void enqueue(request ** head, request * req);

/* read */
int read_header(request * req);
int read_body(request * req);
int write_body(request * req);

/* request */
request *new_request(void);
void get_request(int);
void process_requests(int server_s);
int process_header_end(request * req);
int process_header_line(request * req);
int process_logline(request * req);
int process_option_line(request * req);
void add_accept_header(request * req, char *mime_type);
void free_requests(void);
s_param **param_line (char *line,char separate1,char separate2);
void free_param(s_param **var);
struct passwd *getrealpass(const char *user) ;


/* response */
void print_ka_phrase(request * req);
void print_content_type(request * req);
void print_content_length(request * req);
void print_last_modified(request * req);
void print_http_headers(request * req);

void send_r_request_ok(request * req); /* 200 */
void send_r_moved_perm(request * req, char *url); /* 301 */
void send_r_moved_temp(request * req, char *url, char *more_hdr); /* 302 */
#if defined(TCSUPPORT_SELF_LOGIN_WINDOW) || defined(TCSUPPORT_WEB_INTERCEPTION)
void send_r_moved_temp_new(request * req, char *url, char *more_hdr);
#endif
void send_r_not_modified(request * req); /* 304 */
void send_r_bad_request(request * req); /* 400 */
void send_r_cannot_login(request * req); /* 400 */ /* Paul add 2013/1/3 */
void send_r_unauthorized(request * req, char *name); /* 401 */
void send_r_forbidden(request * req); /* 403 */
void send_r_not_found(request * req); /* 404 */
void send_r_error(request * req); /* 500 */
void send_r_not_implemented(request * req); /* 501 */
void send_r_bad_gateway(request * req); /* 502 */
void send_r_service_unavailable(request * req); /* 503 */
void send_r_bad_version(request * req); /* 505 */
void send_r_password_page(request *req, char* url);
void send_r_login_page(request *req, int error_status, char* url, int lock_time);

/* cgi */
void create_common_env(void);
void clear_common_env(void);
int add_cgi_env(request * req, char *key, char *value, int http_prefix);
int complete_env(request * req);
void create_argv(request * req, char **aargv);
int init_cgi(request * req);

/* signals */
void init_signals(void);
void sighup_run(void);
void sigchld_run(void);
void sigalrm_run(void);
void sigterm_stage1_run(int);
void sigterm_stage2_run();

/* util.c */
void clean_pathname(char *pathname);
char *get_commonlog_time(void);
void rfc822_time_buf(char *buf, time_t s);
char *simple_itoa(unsigned int i);
int boa_atoi(char *s);
char *escape_string(char *inp, char *buf);
int month2int(char *month);
int modified_since(time_t * mtime, char *if_modified_since);
char *to_upper(char *str);
int unescape_uri(char *uri, char **query_string);
int create_temporary_file(short want_unlink, char *storage, int size);
char * normalize_path(char *path);
int real_set_block_fd(int fd);
int real_set_nonblock_fd(int fd);
int check_current_ip_is_lan_or_wan(const char *target_ip);
int check_xss_blacklist(char* para, int check_www);
login_retry_t* get_login_retry_by_url(const char* remote_ip);

/* buffer */
int req_write(request * req, char *msg);
void reset_output_buffer(request *req);
int req_write_escape_http(request * req, char *msg);
#if defined(TCSUPPORT_SELF_LOGIN_WINDOW) || defined(TCSUPPORT_WEB_INTERCEPTION)
int req_write_escape_http_new(request * req, char *msg);
#endif
int req_write_escape_html(request * req, char *msg);
int req_flush(request * req);
char *escape_uri(char *uri);

/* timestamp */
void timestamp(void);

/* mmap_cache */
struct mmap_entry *find_mmap(int data_fd, struct stat *s);
void release_mmap(struct mmap_entry *e);

/* sublog */
int open_gen_fd(char *spec);
int process_cgi_header(request * req);

/* pipe */
int read_from_pipe(request * req);
int write_from_pipe(request * req);

/* ip */
int bind_server(int server_s, char *ip);
char *ascii_sockaddr(struct SOCKADDR *s, char *dest, int len);
int net_port(struct SOCKADDR *s);

/* select */
void select_loop(int server_s);

#if defined(TCSUPPORT_WEBSERVER_SSL)
extern int ssl_server_port;
extern int http_mode;
int boa_sslInit();
void boa_sslUninit();
int boa_sslAccept(mssl_conn_t **conn, const int fd, SSL_CTX *ctx);
int boa_sslWrite(mssl_conn_t *conn, char *buf, const int buflen);
int boa_sslRead(mssl_conn_t *conn, char *buf, const int len);
int boa_sslClose(mssl_conn_t *conn);

enum { HTTP_ONLY = 1, HTTPS_ONLY, BOTH_HTTP_HTTPS };
#endif 

void *rfc822_base64 (unsigned char *src,unsigned long srcl,unsigned long *len);

int encryptRomfile(char *src, char *dst, char *productName);
#endif
