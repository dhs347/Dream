struct Link{
	struct node{int id,x; node *nxt;}; node *head,*p;  Link(){ head=NULL; }
	void I(int id,int x) { head=new node{id,x,head}; }
	int F(int id) { for (p=head; p; p=p->nxt) if (p->id==id) return p->x; return 0; }
};
