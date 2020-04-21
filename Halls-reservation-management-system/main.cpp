#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<stdio.h>
using namespace std;
struct date
{
	int D, H;
};
struct events
{
	int ID;
	string name;
	date startEVdate, endEVdate;
};
struct shows
{
	string name;
	date startSHdate, endSHdate;
	int nmofseats;
};
struct hall
{
	string hallname, place;
	events EVE[100];
	shows SHOW[100];
	int sizeEV, sizeSH;
} halls[100];
struct dataownreservation
{
	string reservname2;
	int ownreservationstart, ownreservationend, owntimesart, owntimeend;
} ownreservation[100];
// this is declarations <<<<<<<<<<<
void RESERVATIONS(int &reserv, int &sizeofplaces);
void  HALLSSTRUCT(int &counthalls, int &sizeofplaces);
void HALLSDATES();
void halldisplay(int o);
void HALLS(int &counthalls, int &sizeofplaces);
void shows(int qq, int &reserv, int &sizeofplaces, int &counthalls, int oo, int o, int arr[], int r[][24], int sr[]);
void availabledatesdisplay(int qq, int &reserv, int &sizeofplaces, int &counthalls);
void AVAILABLEDATES(int &counthalls, int &reserv, int &sizeofplaces);
void operation(int & reserv, int &counthalls, int &sizeofplaces);
void deleteefiles(int &sizeofplaces, string username, string password, int&reserv);
void users(int &sizeofplaces, int &counthalls);
void SEARCHRESERVE(int  &sizeofplaces);
void deletehalls(int & counthalls, int &sizeofplaces);
void addhalls(int &counthalls, int &sizeofplaces);
void admin(int& sizeofplaces, int &counthalls);
int main()   //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
{
loop:
	system("color 1f");
	ios_base::sync_with_stdio(false);
	string choice;
	int sizeofplaces = 0, counthalls = 4;
	cout << "Welcome sir\n";
	cout << "admin or user or exit ?\n";
	cin >> choice;
	if (choice == "user")
		users(sizeofplaces, counthalls);
	else if (choice == "admin")
		admin(sizeofplaces, counthalls);
	else if (choice == "exit")
		return 0;
	system("cls");
	goto loop;
	return 0;
}
// this is definitions
void RESERVATIONS(int &reserv, int &sizeofplaces)
{
	if (reserv == 0)
		cout << "none reservations" << endl;
	for (int i = 0; i < reserv; i++)
	{
		if (ownreservation[i].ownreservationend != ownreservation[i].ownreservationstart)
			cout << ownreservation[i].reservname2 << '\t' << " from  " << ownreservation[i].ownreservationstart << "  to " << ownreservation[i].ownreservationend << "  time at  " << ownreservation[i].owntimesart << "  to " << ownreservation[i].owntimeend << endl;
		else
			cout << ownreservation[i].reservname2 << '\t' << "in " << ownreservation[i].ownreservationend << "  time at  " << ownreservation[i].owntimesart << "    to " << ownreservation[i].owntimeend << endl;
	}
	if (reserv > 0)
	{
	res:
		cout << "Do you want to cancel (YES/NO)??" << endl;
		string ans;
		bool isfound = false;
		cin >> ans;
		if (ans == "no" || ans == "NO")
			return;
		else if (ans == "yes" || ans == "YES")
		{
			cout << "how many reservations do you want to cancel ?? \n";
			int z;
			cin >> z;
			if (z <= reserv)
			{
				for (int pow = 0; pow < z; pow++)
				{
					cout << "what do you want to cancel ?(event / show)" << endl;
					string choose;
					cin >> choose;
					if (choose == "event" || choose == "EVENT")
					{
						cout << "the name of event :" << endl;
						cin.ignore();
						getline(cin, choose);
						for (int i = 0; i < sizeofplaces; i++)
						{
							for (int y = 0; y < halls[i].sizeEV; y++)
							{
								if (choose == halls[i].EVE[y].name)
								{
									isfound = true;
							for (int k = y; k < halls[i].sizeEV; k++)
									{
										halls[i].EVE[k] = halls[i].EVE[k + 1];
									}
									halls[i].sizeEV--;
									break;
								}
							}
						}
						if (!isfound)
						{
							cout << "there isn't any reservation by this name\n";
							goto res;
						}
						if (isfound)
						{
							for (int i = 0; i < reserv; i++)
							{
								if ("EVENT NAME: " + choose == ownreservation[i].reservname2)
								{
									isfound = true;
									for (int j = i; j < reserv; j++)
									{
										ownreservation[j] = ownreservation[j + 1];
									}
									reserv--;
									break;
								}
							}
						}
					}
					if (choose == "show" || choose == "SHOW")
					{
						cout << "the name of show :" << endl;
						cin.ignore();
						getline(cin, choose);
						for (int i = 0; i < sizeofplaces; i++)
						{
							for (int y = 0; y < halls[i].sizeSH; y++)
							{
								if (choose == halls[i].SHOW[y].name)
								{
									isfound = true;
									for (int k = y; k < halls[i].sizeSH; k++)
									{
										halls[i].SHOW[k] = halls[i].SHOW[k + 1];
									}
									halls[i].sizeSH--;
									break;
								}
							}
						}
						if (!isfound)
						{
							cout << "there isn't any reservation by this name\n";
							goto res;
						}
						if (isfound)
						{
							for (int i = 0; i < reserv; i++)
							{
								if ("SHOW NAME: " + choose == ownreservation[i].reservname2)
								{
									for (int j = i; j < reserv; j++)
									{
										ownreservation[j] = ownreservation[j + 1];
									}
									reserv--;
									break;
								}
							}
						}
					}
				}
			}
			else
			{
				cout << "your number you want to cancel is bigger than your reservations!\n";
				goto res;
			}
		}
	}
}
void  HALLSSTRUCT(int &counthalls, int &sizeofplaces)
{
	int  y = 0;
	string s, m, c, a;
	for (int i = 0; i<4; ++i)
	{
		c = (i + 1) + '0';
		m = "HALL" + c;
		s = m + ".txt";
		a = m + " show.txt";
		fstream halll(s.c_str());
		halls[i].hallname = "HALL" + c;
		while (halll.good())
		{
			getline(halll, halls[i].EVE[y].name);
			y++;
		}
		halls[i].sizeEV = y;

		y = 0;
		halll.close();
		fstream hallll(a.c_str());
		while (hallll.good())
		{
			getline(hallll, halls[i].SHOW[y].name);
			y++;
		}
		halls[i].sizeSH = y;

		y = 0;
		hallll.close();
	}
	fstream w("addingnames.txt");
	if (w.is_open())
	{
		string s, m;
		while (w.good())
		{
			bool isfound = false;
			getline(w, s);
			int i = 0;
			fstream a(s.c_str());
			halls[counthalls].hallname = s;
			while (a.good())
			{
				getline(a, halls[counthalls].EVE[i].name);
				if (halls[counthalls].EVE[i].name.length() == 0)
				{
					isfound = true;
					break;
				}
				i++;
			}
			if (!isfound)
				halls[counthalls].sizeEV = i;
			else
				halls[counthalls].sizeEV = 0;
			isfound = false;
			a.close();

			m = s + " show";
			fstream b(m.c_str());
			i = 0;
			while (b.good())
			{
				getline(b, halls[counthalls].SHOW[i].name);
				if (halls[counthalls].SHOW[i].name.length() == 0)
				{
					isfound = true;
					break;
				}
				i++;
			}
			if (!isfound)
				halls[counthalls].sizeSH = i;
			else
				halls[counthalls].sizeSH = 0;
			b.close();
			i = 0;

			counthalls++;
		}
	}
	sizeofplaces = 0;
	w.close();
	fstream wp("addingplaces.txt");
	while (wp.good())
	{
		getline(wp, halls[sizeofplaces].place);
		sizeofplaces++;
	}

}
void HALLSDATES()
{
	int  y = 0;
	string s, m, c, q, v, n, a, u;
	for (int i = 0; i<4; ++i)
	{
		c = (i + 1) + '0';
		m = "HALL" + c;
		q = m + " id.txt";
		s = m + " dates.txt";
		v = m + " EVhours.txt";
		n = m + " nmofseats.txt";
		a = m + " showdates.txt";
		u = m + " SHhours.txt";
		fstream halll(s.c_str());
		while (halll.good())
		{
			halll >> halls[i].EVE[y].startEVdate.D >> halls[i].EVE[y].endEVdate.D;
			y++;
		}

		y = 0;
		halll.close();

		fstream halllv(v.c_str());
		while (halllv.good())
		{
			halllv >> halls[i].EVE[y].startEVdate.H >> halls[i].EVE[y].endEVdate.H;
			y++;
		}

		y = 0;
		halllv.close();

		fstream hallll(q.c_str());
		while (hallll.good())
		{
			hallll >> halls[i].EVE[y].ID;
			y++;
		}

		y = 0;
		hallll.close();
		fstream halllq(a.c_str());
		while (halllq.good())
		{
			halllq >> halls[i].SHOW[y].startSHdate.D >> halls[i].SHOW[y].endSHdate.D;
			y++;
		}

		y = 0;
		halllq.close();
		fstream halllvv(u.c_str());
		while (halllvv.good())
		{
			halllvv >> halls[i].SHOW[y].startSHdate.H >> halls[i].SHOW[y].endSHdate.H;
			y++;
		}

		y = 0;
		halllvv.close();
		fstream hallllq(n.c_str());
		while (hallllq.good())
		{
			hallllq >> halls[i].SHOW[y].nmofseats;
			y++;
		}

		y = 0;
		hallllq.close();
	}
	fstream w("addingnames.txt");
	if (w.is_open())
	{
		string s, m, o, p, E, S;
		int z = 4;
		while (w.good())
		{
			getline(w, s);
			int i = 0;
			m = s;
			o = s;
			p = s;
			E = s;
			S = s;
			s += " dates";
			fstream a(s.c_str());
			while (a.good())
			{
				a >> halls[z].EVE[i].startEVdate.D;
				a >> halls[z].EVE[i].endEVdate.D;
				i++;
			}

			a.close();
			i = 0;

			S += " SHhours";
			fstream k(S.c_str());
			while (k.good())
			{
				k >> halls[z].SHOW[i].startSHdate.H;
				k >> halls[z].SHOW[i].endSHdate.H;
				i++;
			}

			a.close();
			i = 0;

			E += " EVhours";
			fstream K(E.c_str());
			while (K.good())
			{
				K >> halls[z].EVE[i].startEVdate.H;
				K >> halls[z].EVE[i].endEVdate.H;
				i++;
			}

			K.close();
			i = 0;

			m += " id";
			fstream q(m.c_str());
			while (q.good())
			{
				q >> halls[z].EVE[i].ID;
				i++;
			}
			q.close();

			i = 0;
			o += " showdates";
			fstream b(o.c_str());
			while (b.good())
			{
				b >> halls[z].SHOW[i].startSHdate.D;
				b >> halls[z].SHOW[i].endSHdate.D;
				i++;
			}

			b.close();
			i = 0;
			p += " nmofseats";
			fstream x(p.c_str());
			while (x.good())
			{
				x >> halls[z].SHOW[i].nmofseats;
				i++;
			}

			x.close();
			i = 0;
			z++;
		}
	}
	w.close();
}
void halldisplay(int o)
{
	for (int i = 0; i<halls[o].sizeEV; i++)
	{
		if (halls[o].EVE[i].startEVdate.D != halls[o].EVE[i].endEVdate.D)
		{
			if (halls[o].EVE[i].startEVdate.D >= 10)
				cout << halls[o].EVE[i].ID << "\t" << halls[o].EVE[i].name << "\t" << "from " << halls[o].EVE[i].startEVdate.D << "       to       " << '\t' << halls[o].EVE[i].endEVdate.D << "   \tat\t\t" << halls[o].EVE[i].startEVdate.H << "\tto\t" << halls[o].EVE[i].endEVdate.H << endl;
			else
				cout << halls[o].EVE[i].ID << "\t" << halls[o].EVE[i].name << "\t" << "from " << halls[o].EVE[i].startEVdate.D << "        to      " << '\t' << halls[o].EVE[i].endEVdate.D << "   \tat\t\t" << halls[o].EVE[i].startEVdate.H << "\tto\t" << halls[o].EVE[i].endEVdate.H << endl;
		}
		else
			cout << halls[o].EVE[i].ID << "\t" << halls[o].EVE[i].name << '\t' << "at " << halls[o].EVE[i].startEVdate.D << "\t\t" << "at " << halls[o].EVE[i].startEVdate.H << "to\t" << halls[o].EVE[i].endEVdate.H << endl;
	}
	if (halls[o].sizeSH != 0)
	{
		cout << "list of shows :\n";
		cout << "name  \t      start date       \t\tend date      seats  \t\t start hour  \t   \t end hour\n";
		for (int i = 0; i < halls[o].sizeSH; i++)
		{
			if (halls[o].SHOW[i].startSHdate.D != halls[o].SHOW[i].endSHdate.D)
			{
				if (halls[o].SHOW[i].startSHdate.D >= 10)
					cout << halls[o].SHOW[i].name << "   \t" << "from " << halls[o].SHOW[i].startSHdate.D << "       to " << '\t' << halls[o].SHOW[i].endSHdate.D << "               " << halls[o].SHOW[i].nmofseats << "   \t        at   " << halls[o].SHOW[i].startSHdate.H << "          \tto\t" << halls[o].SHOW[i].endSHdate.H << endl;
				else
					cout << halls[o].SHOW[i].name << "   \t" << "from " << halls[o].SHOW[i].startSHdate.D << "        to " << '\t' << halls[o].SHOW[i].endSHdate.D << "               " << halls[o].SHOW[i].nmofseats << "   \t        at   " << halls[o].SHOW[i].startSHdate.H << "          \tto\t" << halls[o].SHOW[i].endSHdate.H << endl;
			}
			else
				cout << halls[o].SHOW[i].name << '\t' << "in " << halls[o].SHOW[i].startSHdate.D << "                                " << halls[o].SHOW[i].nmofseats << "   \t        at " << halls[o].SHOW[i].startSHdate.H << "          \tto\t" << halls[o].SHOW[i].endSHdate.H << endl;
		}
	}
	else
		cout << "this hall is empty for shows\n";

}
void shows(int qq, int &reserv, int &sizeofplaces, int &counthalls, int oo, int o, int arr[], int r[][24], int sr[]) {
	int q = 0, x[100] = {}, i = 0, z = 0, k = 0, RR[100][30], sRR[100];
	int R[30][24];  int ss = 0; int tt = 0;  bool ff = false;
	string ansdate, answer;
	//>>>>>>>>>>>>>>>>>>a and shownamesize are the size of show file <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	cout << "available days in this hall:\n";
	if (halls[qq].sizeSH > 0)
	{
		cout << endl << "available seats of shows in this hall:\n";
		for (int j = 0; j < halls[qq].sizeSH; ++j) {
			cout << "available seats of " << halls[qq].SHOW[j].name << " is : " << halls[qq].SHOW[j].nmofseats << endl;
		}
	}
	int t1, t2, user_t[24];   bool anstime = false;  int cc = 0, ccc = 0;

	cout << "do you want to attend or reserve or exit?\n";   string ekhtar;
	cin >> ekhtar;
	if (ekhtar == "attend") {
	ll:	string nmofshow;
		cout << "what the name of the show ?\n";
		cin >> nmofshow;  int we; bool isfound = false;
		for (int i = 0; i < halls[qq].sizeSH; ++i) {
			if (halls[qq].SHOW[i].name == nmofshow) {
				we = i;
				isfound = true;
				break;
			}
		}
		if (isfound) {
			int ticket;
			cout << "how many number of tickets you need ?\n"; cin >> ticket;
			halls[qq].SHOW[we].nmofseats -= ticket;
		}
		else {
			cout << "there isn't any show by this name\n";
			goto ll;
		}
	}
	else if (ekhtar == "reserve") {
		cout << "do you want to book (YES/NO)?!" << endl;
		cin >> ansdate;
		cin.ignore();
		if (ansdate == "NO") {
			cout << "what do you want right now (HALLS/OWN RESERVATIONS/AVAILABLE DATES/SEARCH)?!" << endl;
			getline(cin, answer);
			if (answer == "HALLS")
				HALLS(counthalls, sizeofplaces);
			if (answer == "OWN RESERVATIONS")
				RESERVATIONS(reserv, sizeofplaces);
			if (answer == "AVAILABLE DATES")
				AVAILABLEDATES(counthalls, reserv, sizeofplaces);
			if (answer == "SEARCH")
				SEARCHRESERVE(sizeofplaces);
		}
		else if (ansdate == "YES"){
			Loop5:
          bool isfine = true; //  bool to know if the number is available or not
			cout << "Which day !" << endl;
			int n;
			cin >> n;
			cin.ignore();
			cout << "Time  from: ";   cin >> t1;  cout << "  to: ";  cin >> t2;  cout << endl;
			int ff = t1;
			for (int e = 0; e <= (t2 - t1); e++)
			{
				user_t[e] = ff;   ff++;
			}
			l:
			for (int y = 0; y < i; y++) {
				if (n == x[y]) {

					string name; int seats;
					isfine = false;
					cout << "the name of the show" << endl;
					cin.ignore();
					getline(cin, name);
					for (int i = 0; i < sizeofplaces; ++i)
					{
						for (int j = 0; j<halls[i].sizeSH; ++j)
							if (name == halls[i].SHOW[j].name)
							{
								cout << "there is show by this name before please enter another name\n";
								goto l;
							}

					}
					cout << "the available seats of the the show :";
					cin >> seats;
					halls[qq].SHOW[halls[qq].sizeSH].startSHdate.D = n;
					halls[qq].SHOW[halls[qq].sizeSH].endSHdate.D = n;
					halls[qq].SHOW[halls[qq].sizeSH].nmofseats = seats;
					halls[qq].SHOW[halls[qq].sizeSH].startSHdate.H = t1;
					halls[qq].SHOW[halls[qq].sizeSH].endSHdate.H = t2;
					ownreservation[reserv].ownreservationstart = n;
					ownreservation[reserv].ownreservationend = n;
					ownreservation[reserv].owntimesart = t1;
					ownreservation[reserv].owntimeend = t2;
					ownreservation[reserv].reservname2 = "SHOW NAME: " + name;
					halls[qq].SHOW[halls[qq].sizeSH].name = name;
					reserv++;
					halls[qq].sizeSH++;
					cout << "your registing is succeded *" << endl;
				}
			}
			if (isfine == true) {
				//cout << "not available\nplease enter available day\n ";
				//goto Loop5;
				cc = 0;
				//	cout << o;
				for (int ww = 0; ww < o; ww++)
				{
					//cout << "amr";
					if (n == arr[ww])
					{
						//cout << "loaa";
						for (int e = 0; e <= t2 - t1; e++)
						{
							anstime = false;
							for (int zz = 0; zz <= sr[n - 1]; zz++)
							{
								if (r[n - 1][zz] == user_t[e])
								{
									anstime = true;  cc++; break;
								}
							}
						}
						//		cout << cc << " " << (t2 - t1) + 1;
						if (cc == (t2 - t1) + 1)
							goto l;
						else
						{
							cout << "not available\n";
							cin.ignore();
							goto Loop5;
						}
					}
				}

			}
			cout<<"do you need to reserve again (yes/no)? "; string as;
			cin>>as;
			if(as=="yes") {goto Loop5;}
			else return;
	}
	else if (ekhtar == "exit") { return; }
}
}
void HALLS(int &counthalls, int &sizeofplaces)
{
loophalls:
	int z = 0, cc = 0, o = 0;
	string answer;
	cout << "which hall do you want (HALL1/HALL2/HALL3/HALL4";
	for (int i = 4; i<counthalls; ++i)
		cout << "/" << halls[i].hallname;
	cout << ")" << endl;
	getline(cin, answer);
	int aaa;
	bool isfoundd = false;
	for (int j = 0; j<sizeofplaces; ++j)
	{
		if (answer == halls[j].hallname)
		{
			aaa = j;
			isfoundd = true;
			break;
		}
	}
	if (isfoundd == true)
	{
		if (halls[aaa].sizeEV != 0)
		{
			cout << "hall name : " << answer << "\n";
			cout << "hall place : " << halls[aaa].place << "\n";
			cout << "list hall events \n";
			cout << "ID  \tname  \t        start date          \tend date  \t start hour  \t  \tend hour\n";
			halldisplay(aaa);
		}
		else
			cout << "this HALL is empty for events !\n";
	}
	else
	{
		cout << "enter an valid HALL!" << endl;
		goto loophalls;
	}
}
void availabledatesdisplay(int qq, int &reserv, int &sizeofplaces, int &counthalls)
{
	int q = 0, oo = 0, o = 0, arr[100] = {}, x[100] = {}, i = 0, z = 0, k = 0;      int kk = 0;  int mark = 0;
	int ss = 0; int tt = 0; string ansdate, answer, s;
	int RR[100][30]; int sRR[100]; int R[30][24]; int r[30][24]; int sr[30]; bool ff = false; int sd[100][30];
	for (int y = 0; y<halls[qq].sizeEV; y++)
	{
		k = 0;
		for (int m = halls[qq].EVE[y].startEVdate.D; m <= halls[qq].EVE[y].endEVdate.D; m++)
		{
			arr[o] = m;
			sd[y][m] = o;
			RR[y][k] = m;// dates in file that should be not available
			o++;  k++;
		}
		sRR[y] = k;
		kk += k;
		mark = y;
	}
	oo = o;
	for (int y = 0; y< (halls[qq].sizeSH); y++)
	{
		k = 0;
		for (int m = halls[qq].SHOW[y].startSHdate.D; m <= halls[qq].SHOW[y].endSHdate.D; m++)
		{
			arr[o] = m;
			sd[y][m] = o;
			RR[y + halls[qq].sizeEV][k] = m;// dates in file that should be not available
			o++;  k++;
		}
		sRR[y + halls[qq].sizeEV] = k;
		kk += k;
	}

	sort(arr, arr + o);
	for (int start = 1; start <= 30; start++)
	{
		bool isfound = false;
		for (int y = 0; y < o; y++)
		{
			if (start == arr[y])
				isfound = true;
		}
		if (!isfound)
		{
			x[i] = start;
			cout << x[i] << " ";
			i++;
		}
	}
	cout << "\t" << "all  these days are available in all hours " << endl;
	if (i == 0)
		cout << "not available dates in all hours!\n";
	for (int y = 1; y <= 30; y++)
	{
		ss = 0;  tt = 0;
		for (int i = 0; i < halls[qq].sizeEV + halls[qq].sizeSH; i++)
		{
			for (int Q = 0; Q <= sRR[i]; Q++)
			{
				if (y == RR[i][Q])
				{
					if (i <= mark)
					{
						for (int x = halls[qq].EVE[i].startEVdate.H; x <= halls[qq].EVE[i].endEVdate.H; x++)
						{
							R[y - 1][ss] = x;  ss++;
						}
						if (y == 1)
						{
							for (int x = halls[qq].EVE[i].startEVdate.H; x <= halls[qq].EVE[i].endEVdate.H; x++)
							{
								R[-1][ss] = x;  ss++;
							}
						}
					}
					else
					{
						for (int x = halls[qq].SHOW[i - halls[qq].sizeEV].startSHdate.H; x <= halls[qq].SHOW[i - halls[qq].sizeEV].endSHdate.H; x++)
						{
							R[y - 1][ss] = x;  ss++;
						}
						if (y == 1)
						{
							for (int x = halls[qq].SHOW[i - halls[qq].sizeEV].startSHdate.H; x <= halls[qq].SHOW[i - halls[qq].sizeEV].endSHdate.H; x++)
							{
								R[-1][ss] = x;  ss++;
							}
						}
					}
				}
			}
		}
		for (int H = 1; H <= 24; H++)
		{
			ff = false;
			for (int HH = 0; HH < ss; HH++)
			{
				if (H == R[y - 1][HH])
					ff = true;
			}
			if (ff == false)
			{
				r[y - 1][tt] = H;   tt++;
				sr[y - 1] = tt;
			}
		}
		// for(int w=0;w<sRR[y];w++)
	}
	for (int f = 1; f <= 30; f++)
	{
		for (int y = 0; y < o; y++)
		{
			if (arr[y] == f) {
				if (arr[y] != arr[y - 1]) {
					cout << "In " << f << " available at : ";

					for (int t = 0; t < sr[f - 1]; t++)
					{
						cout << r[f - 1][t] << " ";
					}
					cout << endl;
				}
			}
		}
	}
	string choice;
	//string  answer, s, ansdate;
	cout << "events or shows ?\n";
	cin >> choice;
	if (choice == "events") {
		int t1, t2, user_t[24];   bool anstime = false;  int cc = 0, ccc = 0;
		cout << "do you want to book (YES/NO)?!" << endl;
		cin >> ansdate;
		cin.ignore();
		if (ansdate == "NO")
		{
			cout << "what do you want right now (HALLS/OWN RESERVATIONS/AVAILABLE DATES)?!" << endl;
			getline(cin, answer);
			if (answer == "HALLS")
				HALLS(counthalls, sizeofplaces);
			if (answer == "OWN RESERVATIONS")
				RESERVATIONS(reserv, sizeofplaces);
		}
		else if (ansdate == "YES")
		{
		Loop4:
			bool isfine = true; //  bool to know if the number is available or not
				cout << "Which day !" << endl;
				int n, num;
				cin >> n;
				cin.ignore();
				cout << "Time  from: ";   cin >> t1;  cout << "  to: ";  cin >> t2;  cout << endl;
				int ff = t1;
				for (int e = 0; e <= (t2 - t1); e++)
				{
					user_t[e] = ff;   ff++;
				}
				for (int y = 0; y < i; y++)
				{
					if (n == x[y])
					{

						isfine = false;
						string name;
						cout << "the name of the event" << endl;
						cin.ignore();
						getline(cin, name);
						cout << "enter the ID of your reserv" << endl;
						cin >> num;
						halls[qq].EVE[halls[qq].sizeEV].startEVdate.D = n;
						halls[qq].EVE[halls[qq].sizeEV].endEVdate.D = n;
						halls[qq].EVE[halls[qq].sizeEV].startEVdate.H = t1;
						halls[qq].EVE[halls[qq].sizeEV].endEVdate.H = t2;
						halls[qq].EVE[halls[qq].sizeEV].ID = num;
						ownreservation[reserv].ownreservationstart = n;
						ownreservation[reserv].ownreservationend = n;
						ownreservation[reserv].owntimesart = t1;
						ownreservation[reserv].owntimeend = t2;
						ownreservation[reserv].reservname2 = "EVENT NAME: " + name;
						reserv++;
						halls[qq].EVE[halls[qq].sizeEV].name = name;
						halls[qq].sizeEV++;
						cout << "your registing is succeded *" << endl;
					}
				}
				if (isfine == true)
				{
					cc = 0;
					for (int ww = 0; ww < o; ww++)
					{
						if (n == arr[ww])
						{
							for (int e = 0; e <= t2 - t1; e++)
							{
								anstime = false;
								for (int zz = 0; zz <= sr[n - 1]; zz++)
								{
									if (r[n - 1][zz] == user_t[e])
									{
										anstime = true;  cc++;
									}
								}
							}
							if (anstime == true && cc == (t2 - t1) + 1)
							{
								anstime = false;

							}
							else
							{
								cout << "not available\n";    goto Loop4;
							}
						}
					}
				}

			}
			string az;  cout<<"do you want to book again (yes/no) ? ";
			cin>>az;
			if(az=="yes"){
                goto Loop4;
			} else return;
	}
	//_____________________________________________________________________________________________

	else if (choice == "shows") {
		shows(qq, reserv, sizeofplaces, counthalls, oo, o, arr, r, sr);
	}
}
void SEARCHRESERVE(int  &sizeofplaces)
{
	string answer, answer2;
	bool isfound = false;
	cout << "what do you want to search about (EVENT/SHOW)?!\n";
	cin >> answer;
	if (answer == "EVENT")
	{
		cout << "enter the name of the event\n";
		cin >> answer2;
		for (int i = 0; i < sizeofplaces; ++i)
		{
			for (int y = 0; y < halls[i].sizeEV; ++y)
			{
				if (answer2 == halls[i].EVE[y].name)
				{
					isfound = true;
					cout << "your event in " << halls[i].hallname << endl;
					break;
				}
			}
			if (isfound)
				break;
		}
		if (!isfound)
			cout << "there isn't any EVENT by this name unfortunately\n";
	}
	if (answer == "SHOW")
	{
		cout << "enter the name of the show\n";
		cin >> answer2;
		for (int i = 0; i < sizeofplaces; ++i)
		{
			for (int y = 0; y < halls[i].sizeSH; ++y)
			{
				if (answer2 == halls[i].SHOW[y].name)
				{
					isfound = true;
					cout << "your show in " << halls[i].hallname << endl;
					break;
				}
			}
			if (isfound)
				break;
		}
		if (!isfound)
			cout << "there isn't any SHOW by this name unfortunately\n";
	}
}
void AVAILABLEDATES(int &counthalls, int &reserv, int &sizeofplaces)
{
	int q = 0, o = 0, arr[100], x[100], i = 0, z = 0, qq = 0, aaa;
	string ansdate, answer, s;
	cout << "which hall do you want to see its available dates(HALL1/HALL2/HALL3/HALL4";
	fstream w("addingnames.txt");
	if (w.is_open())
	{
		while (w.good())
		{
			getline(w, s);
			cout << "/" << s;
			z++;
		}
	}
	cout << ")" << endl;
	w.close();
	getline(cin, ansdate);
	bool isfoundd = false;
	for (int j = 0; j<sizeofplaces; ++j)
	{
		if (ansdate == halls[j].hallname)
		{
			aaa = j;
			isfoundd = true;
			break;
		}
	}
	if (isfoundd)
		availabledatesdisplay(aaa, reserv, sizeofplaces, counthalls);
	else if (!isfoundd)
	{
		cout << "enter a right HALL from choises please\n";
		AVAILABLEDATES(counthalls, reserv, sizeofplaces);
	}

}
void operation(int & reserv, int &counthalls, int &sizeofplaces)
{
	string answer;
	cout << "what do you want right now (HALLS/OWN RESERVATIONS/AVAILABLE DATES/SEARCH)?!" << endl;
	cin.ignore();
	getline(cin, answer);
	if (answer == "HALLS")
		HALLS(counthalls, sizeofplaces);
	if (answer == "OWN RESERVATIONS")
		RESERVATIONS(reserv, sizeofplaces);
	if (answer == "AVAILABLE DATES")
		AVAILABLEDATES(counthalls, reserv, sizeofplaces);
	if (answer == "SEARCH")
		SEARCHRESERVE(sizeofplaces);
}
void deleteefiles(int &sizeofplaces, string username, string password, int&reserv)
{

	string s;
	remove("HALL1.txt");
	remove("HALL2.txt");
	remove("HALL3.txt");
	remove("HALL4.txt");
	remove("HALL1 dates.txt");
	remove("HALL2 dates.txt");
	remove("HALL3 dates.txt");
	remove("HALL4 dates.txt");
	remove("HALL1 showdates.txt");
	remove("HALL2 showdates.txt");
	remove("HALL3 showdates.txt");
	remove("HALL4 showdates.txt");
	remove("HALL1 id.txt");
	remove("HALL2 id.txt");
	remove("HALL3 id.txt");
	remove("HALL4 id.txt");
	remove("HALL1 nmofseats.txt");
	remove("HALL2 nmofseats.txt");
	remove("HALL3 nmofseats.txt");
	remove("HALL4 nmofseats.txt");
	remove("HALL1 show.txt");
	remove("HALL2 show.txt");
	remove("HALL3 show.txt");
	remove("HALL4 show.txt");
	remove("HALL1 SHhours.txt");
	remove("HALL2 SHhours.txt");
	remove("HALL3 SHhours.txt");
	remove("HALL4 SHhours.txt");
	remove("HALL1 EVhours.txt");
	remove("HALL2 EVhours.txt");
	remove("HALL3 EVhours.txt");
	remove("HALL4 EVhours.txt");
	remove(username.c_str());
	fstream w("addingnames.txt");
	if (w.is_open())
	{
		string s, m, p, k, n, ev, sh;
		int i = 4;
		while (w.good())
		{
			getline(w, s);
			m = s;
			p = s;
			k = s;
			n = s;
			ev = s;
			sh = s;
			remove(s.c_str());
			ofstream a(s.c_str());
			for (int y = 0; y<halls[i].sizeEV; y++)
			{
				a << halls[i].EVE[y].name;
				if (y<halls[i].sizeEV - 1)
					a << endl;
			}
			a.close();
			s += " dates";
			remove(s.c_str());
			ofstream b(s.c_str());
			for (int y = 0; y<halls[i].sizeEV; y++)
			{
				b << halls[i].EVE[y].startEVdate.D << " " << halls[i].EVE[y].endEVdate.D;
				if (y<halls[i].sizeEV - 1)
					b << endl;
			}
			b.close();
			m += " id";
			remove(m.c_str());
			ofstream c(m.c_str());
			for (int y = 0; y<halls[i].sizeEV; y++)
			{
				c << halls[i].EVE[y].ID;
				if (y<halls[i].sizeEV - 1)
					c << endl;
			}
			c.close();
			p += " show";
			remove(p.c_str());
			ofstream q(p.c_str());
			for (int y = 0; y<halls[i].sizeSH; y++)
			{
				q << halls[i].SHOW[y].name;
				if (y<halls[i].sizeSH - 1)
					q << endl;
			}
			q.close();
			k += " nmofseats";
			remove(k.c_str());
			ofstream aa(k.c_str());
			for (int y = 0; y<halls[i].sizeSH; y++)
			{
				aa << halls[i].SHOW[y].nmofseats;
				if (y<halls[i].sizeSH - 1)
					aa << endl;
			}
			aa.close();
			n += " showdates";
			remove(n.c_str());
			ofstream aaa(n.c_str());
			for (int y = 0; y<halls[i].sizeSH; y++)
			{
				aaa << halls[i].SHOW[y].startSHdate.D << " " << halls[i].SHOW[y].endSHdate.D;
				if (y<halls[i].sizeSH - 1)
					aaa << endl;
			}
			aaa.close();

			sh += " SHhours";
			remove(sh.c_str());
			ofstream as(sh.c_str());
			for (int y = 0; y<halls[i].sizeSH; y++)
			{
				as << halls[i].SHOW[y].startSHdate.H << " " << halls[i].SHOW[y].endSHdate.H;
				if (y<halls[i].sizeSH - 1)
					as << endl;
			}
			as.close();

			ev += " EVhours";
			remove(ev.c_str());
			ofstream cv(ev.c_str());
			for (int y = 0; y<halls[i].sizeEV; y++)
			{
				cv << halls[i].EVE[y].startEVdate.H << " " << halls[i].EVE[y].endEVdate.H;
				if (y<halls[i].sizeEV - 1)
					cv << endl;
			}
			cv.close();
			i++;
		}
	}
	for (int i = 0; i <= 3; i++)
	{
		s = halls[i].hallname + ".txt";
		ofstream HALL1OF(s.c_str());
		for (int y = 0; y<halls[i].sizeEV; y++)
		{
			HALL1OF << halls[i].EVE[y].name;
			if (y<halls[i].sizeEV - 1)
				HALL1OF << endl;
		}
		HALL1OF.close();
		s = halls[i].hallname + " id.txt";
		ofstream HALLlOF(s.c_str());
		for (int y = 0; y<halls[i].sizeEV; y++)
		{
			HALLlOF << halls[i].EVE[y].ID;
			if (y<halls[i].sizeEV - 1)
				HALLlOF << endl;
		}
		HALLlOF.close();
		s = halls[i].hallname + " dates.txt";
		ofstream HALLllOF(s.c_str());
		for (int y = 0; y<halls[i].sizeEV; y++)
		{
			HALLllOF << halls[i].EVE[y].startEVdate.D << " ";
			HALLllOF << halls[i].EVE[y].endEVdate.D;
			if (y<halls[i].sizeEV - 1)
				HALLllOF << endl;
		}
		HALLllOF.close();
		s = halls[i].hallname + " showdates.txt";
		ofstream HALLllOFf(s.c_str());
		for (int y = 0; y<halls[i].sizeSH; y++)
		{
			HALLllOFf << halls[i].SHOW[y].startSHdate.D << " ";
			HALLllOFf << halls[i].SHOW[y].endSHdate.D;
			if (y<halls[i].sizeSH - 1)
				HALLllOFf << endl;
		}
		HALLllOFf.close();
		s = halls[i].hallname + " show.txt";
		ofstream HALllOFf(s.c_str());
		for (int y = 0; y<halls[i].sizeSH; y++)
		{
			HALllOFf << halls[i].SHOW[y].name;
			if (y<halls[i].sizeSH - 1)
				HALllOFf << endl;
		}
		HALllOFf.close();
		s = halls[i].hallname + " nmofseats.txt";
		ofstream HLllOFf(s.c_str());
		for (int y = 0; y<halls[i].sizeSH; y++)
		{
			HLllOFf << halls[i].SHOW[y].nmofseats;
			if (y<halls[i].sizeSH - 1)
				HLllOFf << endl;
		}
		HLllOFf.close();

		s = halls[i].hallname + " SHhours.txt";
		ofstream Hallsh(s.c_str());
		for (int y = 0; y<halls[i].sizeSH; y++)
		{
			Hallsh << halls[i].SHOW[y].startSHdate.H << " " << halls[i].SHOW[y].endSHdate.H;
			if (y<halls[i].sizeSH - 1)
				Hallsh << endl;
		}
		Hallsh.close();

		s = halls[i].hallname + " EVhours.txt";
		ofstream Hallev(s.c_str());
		for (int y = 0; y<halls[i].sizeEV; y++)
		{
			Hallev << halls[i].EVE[y].startEVdate.H << " " << halls[i].EVE[y].endEVdate.H;
			if (y<halls[i].sizeEV - 1)
				Hallev << endl;
		}
		Hallev.close();

	}
	ofstream USER(username.c_str());
	USER << username << endl;
	USER << password;
	for (int i = 0; i<reserv; i++)
		USER << endl << ownreservation[i].reservname2 << endl << ownreservation[i].ownreservationstart << " " << ownreservation[i].ownreservationend << " " << ownreservation[i].owntimesart << " " << ownreservation[i].owntimeend;
	USER.close();

}
void users(int &sizeofplaces, int &counthalls)
{
	string username, password;
	int reserv = 0, n;
	HALLSSTRUCT(counthalls, sizeofplaces);
	HALLSDATES();
	cout << "what do you want (register/login/exit)" << endl;
	string answer;
	cin >> answer;
	if (answer == "login")
	{
	loop1:
		cout << "username" << endl;
		cin >> username;
		cout << "password" << endl;
		cin >> password;
		fstream a(username.c_str());
		if (a.is_open())
		{
			bool isfound = false;
			string text;
			int counter = 0;
			while (a.good())
			{
				getline(a, text);
				if (counter == 0)
					username = text;
				counter++;
				if (counter == 2 && text == password)
				{
					isfound = true;
					password = text;
					cout << "Welocome:" << username << endl;
				}
				else if (counter == 2 && text != password)
				{
					cout << "wrong password" << '\n';
					cout << "what do you want right now(register/login/exit)?" << '\n';
					cin >> answer;
					if (answer == "login")
						goto loop1;
					else if (answer == "exit")
					{
						return;
					}
				}
				else if (counter >= 3)
				{
					ownreservation[reserv].reservname2 = text;
					a >> n;
					ownreservation[reserv].ownreservationstart = n;
					a >> n;
					ownreservation[reserv].ownreservationend = n;
					a >> n;
					ownreservation[reserv].owntimesart = n;
					a >> n;
					ownreservation[reserv].owntimeend = n;
					a.ignore();
					reserv++;
				}
			}
			counter = 0;
			if (isfound)
			{
				operation(reserv, counthalls, sizeofplaces);
				cout << "do you want to EXIT!(YES/NO)" << endl;
				cin >> answer;
				while (answer == "NO")
				{
					operation(reserv, counthalls, sizeofplaces);
					cout << "do you want to EXIT!(YES/NO)" << endl;
					cin >> answer;
				}
			}
		}
		else
		{
			cout << "wrong username" << '\n';
			cout << "what do you want right now(register/login/exit)?" << '\n';
			cin >> answer;
			if (answer == "login")
				goto loop1;
			else if (answer == "exit")
			{
				return;
			}
		}
		a.close();
	}
	if (answer == "register")
	{
		cout << "username" << endl;
		cin >> username;
		cout << "password" << endl;
		cin >> password;
		cout << "Welocome:" << username << endl;
		ofstream f(username.c_str());
		f << username << endl << password;
		f.close();
		operation(reserv, counthalls, sizeofplaces);
		cout << "do you want to EXIT!(YES/NO)" << endl;
		cin >> answer;
		while (answer == "NO")
		{
			operation(reserv, counthalls, sizeofplaces);
			cout << "do you want to EXIT!(YES/NO)" << endl;
			cin >> answer;
		}
	}
	deleteefiles(sizeofplaces, username, password, reserv);
}
void deletehalls(int & counthalls, int &sizeofplaces)
{
ll:
	if (counthalls > 4)
	{
		string namedelete, as, aa, placedelete, asshow, asdates, asseats;
		cout << "what the name of hall you want to delete it? (";
		for (int i = 4; i<counthalls; i++)
		{
			cout << halls[i].hallname;
			if (i<counthalls - 1)
				cout << "/";
		}
		cout << ")" << endl;
		cin >> namedelete;
		int qq = 0;
		for (int n = 4; n<counthalls; ++n)
		{
			if (halls[n].hallname == namedelete)
				qq++;
		}
		if (qq>0)
		{
			string ashourssh, ashoursev;
			int z;
			aa = namedelete;
			as = namedelete;
			asshow = namedelete;
			asdates = namedelete;
			asseats = namedelete, ashoursev = namedelete, ashourssh = namedelete;
			asshow += " show";
			asdates += " showdates";
			asseats += " nmofseats";
			remove(asshow.c_str());
			remove(asdates.c_str());
			remove(asseats.c_str());
			remove(namedelete.c_str());
			namedelete += " dates";
			remove(namedelete.c_str());
			ashoursev += " EVhours";
			remove(ashoursev.c_str());
			ashourssh += " SHhours";
			remove(ashourssh.c_str());
			as += " id";
			remove(as.c_str());
			remove("addingnames.txt");
			if (counthalls > 5)
			{
				ofstream w("addingnames.txt");
				for (int i = 4; i < counthalls; i++)
				{
					if (aa != halls[i].hallname)
					{
						w << halls[i].hallname;
						if (i < counthalls - 1)
							w << endl;
					}
					else
						z = i;
				}
			}
			remove("addingplaces.txt");
			ofstream wp("addingplaces.txt");
			for (int i = 0; i<sizeofplaces; i++)
			{
				if (aa != halls[i].hallname)
				{
					wp << halls[i].place;
					if (i<sizeofplaces - 1)
						wp << endl;
				}
			}
			wp.close();
			counthalls--;
			sizeofplaces--;
			cout << "you deleted (" << aa << " hall) successfully \n";
		}
		else
		{
			cout << "enter available HALL to delete /n";
			goto ll;
		}
	}
	else
		cout << "there isn't any available HALL to delete!\n";
}
void addhalls(int &counthalls, int &sizeofplaces)
{

	int n, q = 0;
	HALLSSTRUCT(counthalls, sizeofplaces);
	string s, m, which;
	cout << "welcome admin \n" << "do you need to add or delete halls?\n";
	string enter;
	cin >> enter;
	if (enter == "add")
	{
	loop0:
		string a, s, d, f, places;
		int numofevent;
		cout << "how many number of halls you need to add? ";
		cin >> n;
		while (q<n)
		{
			string name, z1, z2;
			cout << "Enter the name of hall number " << q + 1 << " \n";
			cin.ignore();
			getline(cin, name);
			ofstream name1(name.c_str());
			halls[counthalls].hallname = name;
			cout << "Enter the place of hall number " << q + 1 << "\n";
			getline(cin, places);
			halls[sizeofplaces].place = places;
			counthalls++;
			sizeofplaces++;
			cout << "do you want to create events and shows for this hall(yes/no)?";
			cin >> which;
			if (which == "no")
			{
				z1 = name + " show";
				ofstream as(z1.c_str());
				z1 = name + " showdates";
				ofstream ass(z1.c_str());
				z1 = name + " dates";
				ofstream assss(z1.c_str());
				z1 = name + " EVhours";
				ofstream asqs(z1.c_str());
				z1 = name + " SHhours";
				ofstream asq(z1.c_str());
				z1 = name + " id";
				ofstream asw(z1.c_str());
				z2 = name + " nmofseats";
				ofstream asss(z2.c_str());
				remove("addingnames.txt");
				ofstream a("addingnames.txt");
				if (a.is_open())
				{

					for (int i = 4; i < counthalls; i++)
					{
						a << halls[i].hallname;
						if (i < counthalls - 1)
							a << endl;
					}
				}
				a.close();
				remove("addingplaces.txt");
				ofstream aa("addingplaces.txt");
				if (aa.is_open())
				{
					for (int i = 0; i<sizeofplaces; i++)
					{
						aa << halls[i].place;
						if (i<sizeofplaces - 1)
							aa << endl;
					}
				}
				aa.close();
				q++;
			}
			else if (which == "yes")
			{
				cout << "how many number of events you need to add? ";
				cin >> numofevent;
				cout << "please add (" << numofevent << ") events names of (" << name << ") hall:\n";
				int i = 0;
				while (i<numofevent)
				{
					cout << "event number " << i + 1 << "\n";
					cout << "event name :";
					cin >> s;
					name1 << s;
					if (i<numofevent - 1)
					{
						name1 << endl;
					}
					i++;
				}
				i = 0;
				name1.close();
				ofstream id1;
				string z;
				z = name + " id";
				id1.open(z.c_str());
				cout << "please add the events id of (" << name << ") hall:\n";
				while (i<numofevent)
				{
					cout << "event number " << i + 1 << "\n";
					cout << "event id :";
					cin >> a;
					id1 << a;
					if (i<numofevent - 1)
					{
						id1 << endl;
					}
					i++;
				}
				id1.close();
				i = 0;
				ofstream hours;
				z = name + " EVhours";
				hours.open(z.c_str());
				cout << "please add the events hours of (" << name << ") hall:\n";
				while (i<numofevent)
				{
					cout << "event number " << i + 1 << "\n";
					cout << "start hour and end hour :\n";
					cin >> d >> f;
					hours << d << " " << f;
					if (i<numofevent - 1)
					{
						hours << endl;
					}
					i++;
				}
				i = 0;
				hours.close();
				ofstream dates;
				string startdate, enddate, x;
				x = name + " dates";
				cout << "Enter the (start and end) dates of (" << name << ") hall\n";
				dates.open(x.c_str());
				while (i<numofevent)
				{
					cout << "event number " << i + 1 << "\n";
					cout << "start and end dates :";
					cin >> d >> f;
					dates << d << " " << f;
					if (i<numofevent - 1)
					{
						dates << endl;
					}
					i++;
				}
				i = 0;
				int numofshow;
				cout << "how many number of shows you need to add? ";
				cin >> numofshow;
				string nmofshow, f1, f2, f3;
				nmofshow = name + " show";
				ofstream na(nmofshow.c_str());
				cout << "please add (" << numofshow << ") shows names of (" << name << ") hall:\n";
				while (i<numofshow)
				{
					cout << "show number " << i + 1 << "\n";
					cout << "show name :";
					cin >> f1;
					na << f1;
					if (i<numofshow - 1)
					{
						na << endl;
					}
					i++;
				}
				i = 0;
				na.close();
				ofstream ns;
				string showdates;
				showdates = name + " showdates";
				cout << "Enter the (start and end) dates of shows of (" << name << ") hall\n";
				ns.open(showdates.c_str());
				while (i<numofshow)
				{
					cout << "show number " << i + 1 << "\n";
					cout << "start and end dates :";
					cin >> f2 >> f3;
					ns << f2 << " " << f3;
					if (i<numofshow - 1)
					{
						ns << endl;
					}
					i++;
				}
				i = 0;
				ns.close();
				ofstream hourss;
				z = name + " SHhours";
				hourss.open(z.c_str());
				cout << "please add the show hours of (" << name << ") hall:\n";
				while (i<numofevent)
				{
					cout << "event number " << i + 1 << "\n";
					cout << "start hour and end hour :\n";
					cin >> d >> f;
					hourss << d << " " << f;
					if (i<numofevent - 1)
					{
						hourss << endl;
					}
					i++;
				}
				i = 0;
				hourss.close();
				ofstream nd;
				int num;
				string nmofseats;
				nmofseats = name + " nmofseats";
				nd.open(nmofseats.c_str());
				cout << "please enter the available seats in this show (maximum 100 seats)\n";
				while (i<numofshow)
				{
				seat:
					cout << "number of seats of show number " << i + 1 << "\n";
					cin >> num;
					if (num>100)
					{
						cout << "\"maximum 100 seats\" please enter valid seats\n";
						goto seat;
					}
					nd << num;
					if (i<numofshow - 1)
					{
						nd << endl;
					}
					i++;
				}
				i = 0;
				nd.close();
				cout << "you added (" << name << " hall) successfully \n";
				cout << "______________________________________________________" << endl;
				q++;
				counthalls++;
				sizeofplaces++;
				remove("addingnames.txt");
				ofstream a("addingnames.txt");
				if (a.is_open())
				{
					for (int i = 4; i<counthalls; i++)
					{
						a << halls[i].hallname;
						if (i<counthalls - 1)
							a << endl;
					}
				}
				a.close();
				remove("addingplaces.txt");
				ofstream aa("addingplaces.txt");
				if (aa.is_open())
				{
					for (int i = 0; i<sizeofplaces; i++)
					{
						aa << halls[i].place;
						if (i<sizeofplaces - 1)
							aa << endl;
					}
				}
				aa.close();
			}
		}
		q = 0;
	}
	else if (enter == "delete")
		deletehalls(counthalls, sizeofplaces);

		remove("addingplaces.txt");
		ofstream aa("addingplaces.txt");
		if (aa.is_open())
		{
			for (int i = 0; i<sizeofplaces; i++)
			{
				aa << halls[i].place;
				if (i<sizeofplaces - 1)
					aa << endl;
			}
		}
		aa.close();
	string ss;
	cout << "Do you want to ((add) or (delete) again) or (exit) ?";
	cin >> ss;
	if (ss == "add")
		goto loop0;
	else if (ss == "delete")
		deletehalls(counthalls, sizeofplaces);
	else if (ss == "exit")
		return;
}
void admin(int& sizeofplaces, int &counthalls)
{
	string username, password;
loop0:
	cout << "Enter username :";
	cin >> username;
	cout << "Enter password :";
	cin >> password;
	if (username == "admin"&&password == "123456")
	{
		addhalls(counthalls, sizeofplaces);
	}
	else
	{
		cout << "\"Not available\"\n";
		string s;
		cout << "you need to (exit) or try again ?";
		cin.ignore();
		getline(cin, s);
		if (s == "try again")
		{
			goto loop0;
		}
		else if (s == "exit")
		{
			return;
		}
	}
}
