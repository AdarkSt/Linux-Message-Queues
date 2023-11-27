#define MSQ_ID 15
#define MAX_MTEXT 1024

struct mbuf{
	long mtype;
	char mtext[MAX_MTEXT];
};

int init_queue();
