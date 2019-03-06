#define MAX_LEN_INT 11
#define DATE_LEN 10
struct expr {
	char arg1[MAX_LEN_INT+1];
	char arg2[MAX_LEN_INT+1];
	char op;
	char date[DATE_LEN];
	struct expr* nextexpr;
};
struct expr* addexpr(struct expr* list,struct expr* expr);
struct expr* rmexpr(struct expr* list, char *date);
struct expr* searchexpr(struct expr* list, char* date);
int strtoexpr(char *buf,struct expr *expr1);
