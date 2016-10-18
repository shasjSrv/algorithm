#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <fstream>
#include "../include/Vec.h"

using namespace std;

#define MAXN 1010

typedef long long vtype;


/* Original points in the input. */
vec3 A[MAXN];

/* E[i][j] indicates which (up to two) other points combine with the edge i and
 * j to make a face in the hull.  Only defined when i < j.
 */
struct twoset {
	void insert(int x) { (a == -1 ? a : b) = x; }
	bool contains(int x) { return a == x || b == x; }
	void erase(int x) { (a == x ? a : b) = -1; }
	int size() { return (a != -1) + (b != -1); }
	int a, b;
} E[MAXN][MAXN];

struct face {
	vec3 norm;
	vtype disc;
	int I[3];
};

/* Compute the half plane {x : c^T norm < disc}
 * defined by the three points A[i], A[j], A[k] where
 * A[inside_i] is considered to be on the 'interior' side of the face. */
face make_face(int i, int j, int k, int inside_i) {
	E[i][j].insert(k); E[i][k].insert(j); E[j][k].insert(i);

	face f;
	f.I[0] = i; f.I[1] = j; f.I[2] = k;
	f.norm = (A[j] - A[i]) * (A[k] - A[i]);
	f.disc = f.norm.dot(A[i]);
//	cout<<A[i]<<' '<<A[j]<<' '<<A[k]<<endl;
	cout<<f.disc<<endl;
	if(f.norm.dot(A[inside_i]) > f.disc) {
		f.norm = -f.norm;
		f.disc = -f.disc;
	}
	cout<<f.disc<<endl;
	return f;
}

bool init_fourface(int n)
{
	for(int i = 0;i < n;i++){
		
	}
}

int main() {
	/*int N;*/
	/*for(cin >> N; N; cin >> N) {*/
	int N = 0;
	ifstream fi("data");
	if(fi == NULL)
	  return 0;
	while(!fi.eof()){
		fi >> A[N].X[0] >> A[N].X[1] >> A[N].X[2];
		N++;
	}
	/*for(int i = 0; i < N; i++) {*/
		//cin >> A[i].X[0] >> A[i].X[1] >> A[i].X[2];
	/*}*/

	/* Initially construct the hull as containing only the first four points. */
	face f;
	vector<face> faces;
	memset(E, -1, sizeof(E));
	for(int i = 0; i < 4; i++)
	  for(int j = i + 1; j < 4; j++)
		for(int k = j + 1; k < 4; k++) {
			faces.push_back(make_face(i, j, k, 6 - i - j - k));
		}

	/* Now add a point into the hull one at a time. */
	for(int i = 4; i < N; i++) {
		/* Find and delete all faces with their outside 'illuminated' by this
		 * point. */
		for(int j = 0; j < faces.size(); j++) {
			f = faces[j];
			if(f.norm.dot(A[i]) > f.disc) {
				E[f.I[0]][f.I[1]].erase(f.I[2]);
				E[f.I[0]][f.I[2]].erase(f.I[1]);
				E[f.I[1]][f.I[2]].erase(f.I[0]);
				faces[j--] = faces.back();
				faces.resize(faces.size() - 1);
			}
		}
		/* Now for any edge still in the hull that is only part of one face
		 * add another face containing the new point and that edge to the hull. */
		int nfaces = faces.size();
		for(int j = 0; j < nfaces; j++) {
			f = faces[j];
			for(int a = 0; a < 3; a++) 
			  for(int b = a + 1; b < 3; b++) {
				  int c = 3 - a - b;
				  if(E[f.I[a]][f.I[b]].size() == 2) continue;
				  faces.push_back(make_face(f.I[a], f.I[b], i, f.I[c]));
			  }
		}
	}
	for(int i = 0; i < faces.size(); i++)
	{
		cout<<faces[i].I[0]<<faces[i].I[1]<<faces[i].I[2]<<endl;
	}

}
