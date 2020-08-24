#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<iomanip>
using namespace std;

class p{
public:
	double x, y;
	p(){};
	p(double x, double y, int i){this->x = x ; this->y = y;};
};

double dis(p a, p b){
	double dx, dy;
	dx = a.x - b.x;
	dy = a.y - b.y;
	return (dx * dx + dy * dy);
}

bool cmpx(p a, p b){
	return a.x < b.x;
}

bool cmpy(p a, p b){
	return a.y < b.y;
}


double closest_pair_rec(vector<p> px, vector<p> py){
	double min_q, min_r, min;
	int num = px.size();
	if(num == 0 || num == 1){
		return 200000000;
	}
	else if(num == 3|| num == 2){
		double min_d = dis(px[0], px[1]);
		for(int i = 0; i < num-1; i++){
			for(int j = i+1; j < num; j++){
				min_d = (dis(px[i], px[j]) > min_d)?min_d : dis(px[i], px[j]);
			}
		}

		return min_d;
	}
	
	vector<p> qx, 
			  qy, 
			  rx, 
			  ry;
	qx.assign(px.begin(),px.begin()+(int)(px.size()/2));
	qy.assign(py.begin(),py.begin()+(int)(py.size()/2));
	rx.assign(px.begin()+(int)(px.size()/2)+1,px.end());
	ry.assign(py.begin()+(int)(py.size()/2)+1,py.end());


	min_q = closest_pair_rec(qx, qy);
	min_r = closest_pair_rec(rx, ry);

	min = (min_q > min_r) ? min_r : min_q;
	int c = px.size()/2;
	double cx = px[c].x;
	vector<p> set_c;
	int i = 0;
	while(i < num){
		if(abs(px[i].x- cx) < min){
			set_c.push_back(px[i]);
		}
		i++;
	}
	sort(set_c.begin(), set_c.end(),cmpy);

	int curr = 0;
	double min_c = 200000000;
	while(curr < set_c.size()){
		for(int i = curr+1; i < curr+8 && i < set_c.size(); i++){

			min_c = (dis(set_c[curr], set_c[i]) > min_c)? min_c : dis(set_c[curr], set_c[i]);
		}
		curr++;
	}

	min = (min_c > min)? min : min_c;
	return min;
	
}

void closest_pair(vector<p> s){
	vector<p> px, py;
	sort(s.begin(),s.end(),cmpx);
	px.assign(s.begin(), s.end());
	sort(s.begin(),s.end(),cmpy);
	py.assign(s.begin(), s.end());
	
	cout<<fixed<<setprecision(2)<<closest_pair_rec(px, py)<<endl;
}



int main(){
	int num;
	cin>>num;
	vector<p> s;
	p a;
	for(int i = 0; i < num ; i++){
		cin>>a.x>>a.y;
		s.push_back(a);
	}

	closest_pair(s);
	return 0;
}