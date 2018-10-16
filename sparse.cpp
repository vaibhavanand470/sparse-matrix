//Assignment-2
//Name: Vaibhav Anand
//Roll No.: CSE170001053

#include<iostream>

using namespace std;

struct node
{
	int rno, cid;
	float marks;
	node *side, *down;
};

void countdown(node *h, int c) //counts the no. of nodes below a leading course node(cid = c).
{
 	node *ptr = h->side;
 	while(ptr->cid != c)
 		ptr = ptr->side;
 	
	ptr->rno = 0;
 	for(node *p = ptr; p->down; p = p->down)
 		ptr->rno++;
}

void countside(node *h, int r) //counts the no. of nodes to the right of a leading student node(rno = r).
{
 	node *ptr = h->down;
 	while(ptr->rno != r)
 		ptr = ptr->down;

 	ptr->cid = 0;
 	
	 for(node *p = ptr; p->side; p = p->side)
 		ptr->cid++;
}

void countstud(node *h)	//counts the no. of students in each course and stores it in "rno" of respective leading course node.
{
 	node *ptr = h->side;
 	while(ptr)
 	{
 		countdown(h, ptr->cid);
 		//cout<<"No. of students in course "<<ptr->cid<<" = "<<ptr->rno<<endl;
 		ptr = ptr->side;
 	}
}

void total(node *h, int r) //counts the total marks of student, stores in leading's marks. 
{
 	node *ptr = h->down;
 	while(ptr->rno != r)
 		ptr = ptr->down;
 	
	ptr->marks = 0.0;
	
	for(node *p = ptr; p->side; p = p->side)
 		ptr->marks += p->marks;
}

int avg(node *h, int c) //calculates the average marks in a course, stores in leading's marks.
{
 	node *ptr = h->side;
 	while(ptr->cid != c)
 		ptr = ptr->side;
 
 	ptr->marks = 0.0;

 	for(node *p = ptr->down; p; p = p->down)
 		ptr->marks += (p->marks/ptr->rno);
 	cout << ptr->marks << endl;
}

void alltotal(node *h) //does total() for all students.
{
 	node *ptr = h->down;
 	while(ptr)
 	{
 		total(h, ptr->rno);
 		cout<<"Total marks of student with roll no. "<<ptr->rno<<" = "<<ptr->marks<<endl;
 		ptr = ptr->down;
 	}
}

void allavg(node *h) //does avg() for all courses.
{
 	node *ptr = h->side;
 	while(ptr)
 	{
 		avg(h, ptr->cid);
 		cout<<"Average marks in course "<<ptr->cid<<" = "<<ptr->marks<<endl;
 		ptr = ptr->side;
 	}
} 

void add_course(node *h)
{
	node *ptr = new node, *p = h;
	cout<<"Enter the new course's id: ";
	cin>>ptr->cid;
	while(p->side)
	{
		if(ptr->cid > p->side->cid)
			p = p->side;	
	}
	ptr->side = p->side;
	p->side = ptr;
	++h->cid;
}

void add_stud(node *h)
{
	node *ptr = new node;
	cout<<"Enter the roll no. and no. of courses:";
	cin>>ptr->rno>>ptr->cid;
	node *p = h;
	while(p->down)
	{
		if(ptr->rno > p->down->rno)
			p = p->down;
		else
			break;
	}
	ptr->down = p->down;
	p->down = ptr;
	++h->rno;
}

void remove_course(node *h, int c)
{
	node *p = h, *q = nullptr, *temp = nullptr;
	for(p = h; p; p = p->down)
	{
		q = p;
		while(q->side)
		{
			if(q->side->cid == c)
			{
				temp = q->side;
				q->side = temp->side;
				delete temp;
				break;
				--p->cid;
			}	
			q = q->side;
		}
	}
}

void remove_stud(node *h, int r)
{
	node *p = h, *q = nullptr, *temp = nullptr;
	while(p->down)
	{
		if(p->down->rno == r)
		{
			q = p->down;
			for(int i = 0; i < q->cid; ++i)
			{
				temp = q->side;
				q->side = temp->side;
				delete temp;
			}
			p->down = q->down;
			delete q;
		}
		p = p->down;
	}
	--h->rno;
}

void reg_stud(node *h, int r, int c)
{
	node *ptr = h->side, *stud = new node, *temp = nullptr;
	
	stud->cid = c;
	stud->rno = r;
	stud->marks = 0.0;
	
	while(ptr->cid != c)
	{
		ptr = ptr->side;
	}
	
	++ptr->rno;
	
	while(ptr->down)
	{
		if(ptr->down->rno < r )
			ptr = ptr->down;
		else
			break;
	}
	
	temp = ptr->down;
	ptr->down = stud;
	stud->down = temp;
		
	ptr = h->down;
	while(ptr->rno != r)
	{
		ptr = ptr->down;
	}
	
	++ptr->cid;
	
	while(ptr->side)
	{
		if(ptr->side->cid < c)
			ptr = ptr->side;
		else
			break;
	}
	
	temp = ptr->side;
	ptr->side = stud;
	stud->side = temp;
}

void dereg_stud(node *h, int r, int c)
{
	node *ptr = h->side, *temp = nullptr;
	while(ptr->cid != c)
	{
		ptr = ptr->side;
	}
	
	--ptr->rno;
	
	while(ptr->down->rno != r)
	{
		ptr = ptr->down;
	}
	
	temp = ptr->down;
	ptr->down = temp->down;
	
	ptr = h->down;
	
	while(ptr->rno != r)
	{
		ptr = ptr->down;
	}
	
	--ptr->cid;
	
	while(ptr->side->cid != c)
	{
		ptr = ptr->side;
	}
	
	temp = ptr->side;
	ptr->side = temp->side;
	delete temp;
}

void change_course(node *h, int r, int oc, int nc)
{
	node *ptr = h->side, *temp = nullptr, *t = nullptr;
	while(ptr->cid != oc)
	{
		ptr = ptr->side;
	}
	
	--ptr->rno;
	
	while(ptr->down->rno != r)
	{
		ptr = ptr->down;
	}
	
	temp = ptr->down;
	ptr->down = temp->down;	
	
	ptr = h->side;
	
	while(ptr->cid != nc)
	{
		ptr = ptr->side;
	}
	
	++ptr->rno;	
	
	while(ptr->down)
	{
		if(ptr->down->rno < r)
			ptr = ptr->down;
		else
			break;
	}
	
	ptr->down = temp;
	temp->down = nullptr;
	
	ptr = h->down;
	
	while(ptr->rno != r)
	{
		ptr = ptr->down;
	}
	
	while(ptr->side)
	{
		if(ptr->side->cid < nc)	
			ptr = ptr->side;
		else
			break;
	}
	
	t = ptr->side;
	ptr->side = temp;
	temp->side = t;
	
	temp->cid = nc;
	temp->marks = 0.0;
}

void display(node *h)
{
	cout << "\t";
	for(node *p = h->side; p; p = p->side)
	{
		cout << p->cid <<"\t";
	}
	
	cout << endl;
	node *c = nullptr;
	
	for(node *p = h->down; p; p = p->down)
	{
		cout << p->rno << "\t";
		int cd = 0;
		for(node *q = p->side; q; q = q->side)
		{
			c = h->side;
			while(q->cid != c->cid)
			{
				if(c->cid >= cd) 
				{
					cout << "\t";
				}
				c = c->side;
			}
			
			if(q)
			{
				cout << q->marks; 
				cd = q->cid;
			}
			
		}
		cout << endl;
	}
}

void list_stud(node *h, int c) 
{
	node *ptr = h->side;
	while(ptr->cid != c) 
	{
		ptr = ptr->side;	
	}
	while(ptr->down) 
	{
		cout << ptr->down->rno << endl;
		ptr = ptr->down;
	}
}


void list_course(node *h, int r) 
{
	node *ptr = h->down;
	while(ptr->rno != r) 
	{
		ptr = ptr->down;	
	}
	while(ptr->side) 
	{
		cout << ptr->side->cid << endl;
		ptr = ptr->side;
	}
}

int main()
{
	node *header = new node, *ptr = nullptr, *p = header, *q = nullptr, *ptr2 = nullptr, *r = nullptr;
	cin >> header->cid >> header->rno;
	
	for(int i = 0; i != header->cid; ++i)
	{
		ptr = new node;
		cin >> ptr->cid;
		ptr->side = nullptr;
		ptr->down = nullptr;
		p->side = ptr;
		p = ptr;
	}
	
	p = header;
	q = header->side;
	
	for(int i = 0; i != header->rno; ++i)
	{
		ptr = new node;
		cin >> ptr->rno >> ptr->cid;
		ptr->down = ptr->side = nullptr;
		p->down = ptr;
		p = ptr;
		r = ptr;
		for(int j = 0; j != ptr->cid; ++j)
		{
			q = header->side;
			ptr2 = new node;
			cin >> ptr2->cid >> ptr2->marks;
			ptr2->rno = r->rno;
			r->side = ptr2;
			ptr2->side = nullptr;
			r = ptr2;
			while(q->cid != r->cid)
			{
				q = q->side;
			}
			while(q->down)
			{
				q = q->down;
			}
			q->down = r;
			r->down = nullptr;
		}
	}
	
	countstud(header);
	
	while(true)
	{
		int option;
	    cout << "Choose Any one of the below: " << endl
	         << "1.  Add a student" << endl
	         << "2.  Drop a stdent" << endl
	         << "3.  Add a course" << endl
	         << "4.  Drop a course" << endl
	         << "5.  Register a student to a new course" << endl
	         << "6.  Deregister a student from a course" << endl
	         << "7.  List courses of a student" << endl
	         << "8.  Change a course" << endl
	         << "9.  List students of a given course" << endl
	         << "10. List students with courses and marks" << endl
	         << "11. Average marks of a given course" << endl
	         << "12. Total marks of all courses of a student" << endl
	         << "13. Exit" << endl;
	
	    cin >> option;
	    switch(option)
		{
	        case 1:
	            {
					add_stud(header);
	            	break;
	        	}
	        case 2:
	            {
					int roll_no;
					cout << "Enter roll no.: ";
	            	cin >> roll_no;
	            	remove_stud(header, roll_no);
	            	break;
	        	}
	        case 3:
	            {
					add_course(header);
	            	break;
	        	}
	        case 4:
	            {
					int course_id;
					cout << "Enter course id: ";
	            	cin >> course_id;
	            	remove_course(header, course_id);
	            	break;
	        	}
	        case 5:
	            {
					int roll_no, course_id;
					cout << "Enter roll no. and course id: ";
	            	cin >> roll_no >> course_id;
	            	reg_stud(header, roll_no, course_id);
	            	break;
	        	}
	        case 6:
	        	{
		            int roll_no, course_id;
		            cout << "Enter roll no. and course id: ";
		            cin >> roll_no >> course_id;
		            dereg_stud(header, roll_no, course_id);
		            break;
		        }
	        case 7:
		        {
				    int roll_no;
				    cout << "Enter roll no.: ";
		            cin >> roll_no;
		            list_course(header, roll_no);
		            break;
		    	}
	        case 8:
	            {
					int roll_no, course_id, old_cid, new_cid;
					cout << "Enter roll no., old and new course ids: ";
	            	cin >> roll_no >> old_cid >> new_cid;
	            	change_course(header, roll_no, old_cid, new_cid);
	            	break;
	            }
	        case 9:
	            {
					int course_id;
					cout << "Enter course id: ";
	            	cin >> course_id;
	            	list_stud(header, course_id);
	            	break;
	            }
	        case 10:
	            {
					display(header);
	            	break;
	            }
	        case 11:
	            {
					int course_id;
					cout << "Enter course id: ";
	            	cin >> course_id;
	            	avg(header, course_id);
	            	break;
	            }
	        case 12:
	            {
					alltotal(header);
		            break;
		        }
		    case 13:
		    	{
		    		return 0;
				}
		}
    }
 	
	return 0;
}

