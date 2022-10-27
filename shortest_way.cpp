#include <iostream>
using namespace std;

struct graph{
    int x, y;
    float weight;
};

struct node{
    graph data;
    node* next;
    node* graph;
};

void addLast(node*& first, int x, int y, float weight){
	node* tmp = new node;
	tmp -> next = NULL;
    tmp -> data.x = x;
    tmp -> data.y = y;
    tmp -> data.weight = weight;
	if (first == NULL)
	{
		first = tmp;
	}
	else
	{
		node* p = first;
		while (p != NULL && p -> next != NULL)
			p = p -> next;

		p -> next = tmp;
	}
}

void create_list(node*& first, int n, int x, int y, float weight){
    first = NULL;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y >> weight;
        addLast(first, x, y, weight);
	}
}

void show_list(node* first){
	node* p = first;
    cout << "Граф: " << endl << endl;
	while (p)
	{
		cout << p -> data.x << " " << p -> data.y << " " << p -> data.weight << endl;
		p = p -> next;
	}
    cout << endl;
}

bool check(node*& first, int n, int a, int b){
    node* tmp = first;
    for (int i = 0; i < n; i++){
        if ((tmp -> data.x == a) && (tmp -> data.y == b))
        return true;
        tmp = tmp -> next;
    }
    return false;
}

void matrix(node*& first, int** mat, int n, int m){
    node* kmp = first;
    for (int i = 0; i < n; i++){
        mat[(kmp -> data.x) - 1][(kmp -> data.y) - 1] = kmp -> data.weight;
        mat[(kmp -> data.y) - 1][(kmp -> data.x) - 1] = kmp -> data.weight;
        kmp = kmp -> next;
    }
}

void min(node*& first, int** mat, int* path, int* vis, int n, int m){
    int start, end;
    cout << "Start and end: ";
    cin >> start >> end;
    start--;
    end--;
    int a, b, min; //a - индекс с мин знач, b -   
    for (int i = 0; i < m; i++){
        path[i] = 10000;
        vis[i] = 1;
    }
    path[start] = 0;
    do {
    a = 10000;
    min = 10000;
    for (int i = 0; i < m; i++){
      if ((vis[i] == 1) && (path[i] < min)){ 
        min = path[i];
        a = i;
      }
    }
    if (a < 10000){
      for (int i = 0; i < m; i++){
        if (mat[a][i] > 0){
            b = min + mat[a][i];
            if (b < path[i]){
                path[i] = b;
            }
        }   
      }
      vis[a] = 0;
    }
    } while (a < 10000);
    int vis2[m];
    vis2[0] = end + 1;
    int k = 1;
    int weight = path[end];

    while (end != start){
    for (int i = 0; i < m; i++)
      if (mat[i][end] != 0){
        b = weight - mat[i][end];
        if (b == path[i]){
          weight = b;
          end = i;
          vis2[k] = i + 1;
          k++;
        }
      }
    }
    cout << "Shortest path: ";
    for (int i = k - 1; i >= 0; i--)
        cout << vis2[i] << " ";
    cout << endl << "Length: " << path[k] << endl;


}

int main(){
    node* first = NULL;
    int n, m; //ребра, вершины
    cout << "Amount of ribs and vertices: ";
    cin >> n >> m;
    int** mat = new int *[m];
    for (int i = 0; i < m; i++){
        mat[i] = new int[m];
    }
    int* path = new int[m];
    int* vis = new int[m];
    int x, y;
    float weight;
    create_list(first, n, x, y, weight);
    matrix(first, mat, n, m);
    min(first, mat, path, vis, n, m);

    return 0;
}