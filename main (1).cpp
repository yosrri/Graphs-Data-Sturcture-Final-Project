#include <iostream>
#include<cstdio>

#include <bits/stdc++.h>


using namespace std;
int n;
struct point
{
    int x;
    int y;
};

struct queueNode
{
    point pt;
};

struct flight
{
    int city;
    int cost;
    int time;
};

struct CompareCost {
    bool operator()(flight const& f1,flight const& f2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return f1.cost > f2.cost;
    }
};

int neighborRow[] = {1, 0, 0, -1};
int neighborCol[] = {0, -1, 1, 0};
void fillGPart1(std::vector<std::vector<int> > &G, int M) {
    for (int i = 1; i < M + 1; i++) {
        int u, v;
        cin >> u >> v;
        G[u][v] = 1;          //if there is an edge between two vertices then 1 otherwise it's 0
        G[v][u] = 1;          //undirected graph
    }
}


void printG(std::vector<std::vector<int> > &G, int N) {
    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < N + 1; j++) {
            cout <<" "<< G[i][j] << " ";
        }
        cout << "\n";
    }
}

int partOne(std::queue<int> &Q, std::vector<std::vector<int> > &G, int sV, int kthLevel, int N) {
    int currentLevel = 0;                        //level we are in obviously ya3ne
    std::vector<int> visited(N + 1, 0);  //Vector for visited edges
    Q.push(sV);
    visited[sV] = 1;
//    cout<<Q.front()<<endl;
    int levelSize = 1;                     //knowing the queue size before starting which is 1 obv

    while (!Q.empty()) {
        int i = Q.front();
        int j;
        cout << Q.front() << endl;
        Q.pop();
        for (j = 1; j < N + 1; j++) {
            if (G[i][j] == 1 && visited[j] == 0) {
                visited[j] = 1;
                Q.push(j);
            }
        }
        levelSize--;                                //every time you visit all the neighbors of the current vertex you are in you dequeue so the level size dec also
        if (levelSize ==0)               //when level size reaches zero that means we dequeued all elements for that particular level and we have elements of the next level
        {
            levelSize = Q.size();                     //so we are getting the size of the queue having the next level elements
            currentLevel++;                         //and naturally inc our current level


            if (currentLevel ==kthLevel)            //if the kth level we want initially == our current level that means we have in the queue the elements we need
                return levelSize;
        }
    }
    return 9999;
}




void PartOne(){

    int N, M;               //N Denotes No of Vertices    M Denotes No of Edges
    int sV, kthLevel;
    std::queue<int> Q;


    cout << "Please Enter Number Of Vertices: " << endl;
    cin >> N;
    cout << "Please Enter Number Of Edges: " << endl;
    cin >> M;
    std::vector<std::vector<int> > G(N + 1, std::vector<int>(N + 1, 0));     //Making a 2D Matrix Full Of Zeros N*N Vector Of Vector


    cout << "Please Enter The Edges In The Form Of (u v)" << endl;
    fillGPart1(G, M);     //used to fill the adjacency matrix
    cout << "The Graph In Adjacency Matrix Representation" << endl;
    printG(G, N);


    cout << "Please Enter Starting Vertex: "<<endl;
    cin >> sV;
    cout << "Please enter value of the kth level you wish for: "<<endl;
    cin >> kthLevel;


    int size = partOne(Q, G, sV, kthLevel, N);
    cout << " There are " << size << " people with " << kthLevel
         << " connections away starting from vertex " << sV << " "<< endl;

}

bool check(int x, int y, int n)
{

    return (x >= 0) && (x < n) && (y >= 0) && (y < n);
}


bool PartTwoAlg(vector<vector<int> >& maze, int n, point start, point dest, vector<vector<int> >& solvedMaze)
{

    queue<queueNode> path;
    if(maze[start.x][start.y] == 1 || maze[dest.x][dest.y] == 1)
    {

        return false;
    }
    bool visited[n][n];
    memset(visited, false, sizeof visited);
    visited[start.x][start.y] = true;
    queue<queueNode> q;
    queueNode s;
    s.pt = start;
    q.push(s);
    queueNode solve;

    while(!q.empty())
    {
        queueNode current = q.front();
        point pt = current.pt;

        if(pt.x == dest.x && pt.y == dest.y)
        {

            printf(" (%d,%d) " ,pt.x,pt.y);
            return true;
        }
        else
        {
            path.push(q.front());
            q.pop();

            for(int i = 0; i < 4; i++)
            {
                int row = pt.x + neighborRow[i];
                int col = pt.y + neighborCol[i];
                if(check(row, col, n) == true && maze[row][col] == 0 && visited[row][col] == false )
                {
                    solvedMaze[row][col] = 0;
                    visited[row][col] = true;
                    queueNode neighbor;
                    neighbor.pt.x = row;
                    neighbor.pt.y = col;
                    q.push(neighbor);
                    while(!path.empty())
                    {
                        solve = path.front();
                        printf(" (%d,%d) " ,solve.pt.x,solve.pt.y);
                        path.pop();

                    }


                }
            }

        }

    }

    return false;
}


void PartTwo(){

    int i,j;
    printf("Please enter the maze dimensions: \n");
    scanf("%d",&n);
    vector<vector<int> > maze(n, vector<int>(n));
    printf("Please enter the Values in the maze (0 for a free space you can navigate in and 1 for a block)");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("The Maze[%d][%d] = ",i,j);
            scanf("%d",&maze[i][j]);
        }
    }
    vector<vector<int> > solvedMaze(n, vector<int>(n,1));


    point start;
    point dest;
    start.x = 0;
    start.y = 0;
    dest.x = n-1;
    dest.y = n-1;

    bool path = PartTwoAlg(maze, n, start, dest, solvedMaze);
    if(path == false){
        printf("No path found \n");
    }
    else{
        printf("Path found\n");

    }


}

void PartThreeAlg(list<flight> adj_list[], int s, int d, int M, int N){

    bool visited[N+1];
    int weight[N+1];
    int pathparent[N+1];
    int time[N+1];
    pathparent[s]=s;
    priority_queue <flight, vector<flight>, CompareCost> pq;
    for(int i=1; i<N+1;i++)
    {
        flight ff;
        ff.cost = INT_MAX;
        if(i==s) ff.cost =0;
        visited[i]=false;
        ff.city=i;
        pq.push(ff);
        weight[i]=INT_MAX;
        time[i]=0;
    }
    weight[s]=0;
    flight p;
    int adTime;
    int adCost;
    while(!pq.empty())
    {
        p=pq.top();
        pq.pop();
        int parent = p.city;
        adCost =M;
        adTime = 1;
        if(parent==s)
        {
            adCost=0;
            adTime = 0;
        }
        visited[parent]=true;
        list<flight> l = adj_list[parent];
        list <flight>:: iterator it;
        for ( it=l.begin(); it!=l.end(); it++)
        {
            int mydest;
            flight f = *it;
            mydest=f.city;
            int initCost = f.cost;
            if(weight[parent]+initCost+adCost < weight[mydest] && !visited[mydest])
            {
                weight[mydest] = weight[parent]+initCost+adCost;
                pathparent[mydest]= parent;
                time[mydest]= time[parent]+ adTime+ f.time;
                list<flight> temp;
                flight tempf;
                while(!pq.empty())
                {
                    tempf = pq.top();
                    pq.pop();
                    if(tempf.city == mydest)
                        tempf.cost = weight[mydest];
                    temp.push_back(tempf);
                }
                while(!temp.empty())
                {
                    tempf = temp.front();
                    temp.pop_front();
                    pq.push(tempf);
                }
            }
        }
    }
    stack <int> outpath;
    outpath.push(d);
    int pointer = pathparent[d];
    outpath.push(pointer);
    while(pointer!=s)
    {
        pointer=pathparent[pointer];
        outpath.push(pointer);
    }
    pointer = outpath.top();
    outpath.pop();
    cout << "\nThe route with minimum cost is " ;
    cout << pointer;

    while(!outpath.empty())
    {
        int s = outpath.top();
        cout << "->";
        cout << s;
        outpath.pop();
    }
    cout << "\nTotal time ";
    cout << time[d];
    cout << " hours";
    cout << "\n";
    cout << "Total cost = ";
    cout << weight[d];
    cout <<"$";
}

void PartThree()
{
    int M, N, routes, s,d,t,c,i;
    cout << "please enter amount M: " ;
    cin >> M;
    cout << "please enter number of Cities: " ;
    cin >> N;
    cout << "please enter number of Routes: " ;
    cin >> routes;
    list<flight> adj_list[N+1];
    for(i=1;i<N+1;i++)
    {
        list<flight> L;
        adj_list[i]=L;
    }
    for(i=0;i<routes;i++)
    {
        cout << "please enter source , destination time and cost for each route: ";
        cin >> s;
        cin >> d;
        cin >> t;
        cin >> c;
        int totalcost;
        totalcost = t*M + c;
        flight f1;
        f1.city=d;
        f1.cost = totalcost;
        f1.time =t;
        flight f2;
        f2.city=s;
        f2.cost = totalcost;
        f2.time =t;
        adj_list[s].push_back(f1);
        adj_list[d].push_back(f2);
    }
    int source;
    int destination;
    cout << "please enter source city: ";
    cin >> source;
    cout << "please enter destination city:";
    cin >> destination;
    PartThreeAlg(adj_list,source,destination,M,N);

}



int main()
{
    char g='y';
    int part;
    while(g =='y')
    {

        printf("please choose 1 for part 1, 2 for part 2 , 3 for part 3 \n");
        scanf("%d",&part);
        switch(part)
        {
            case 1: PartOne();break;
            case 2: PartTwo();break;
            case 3: PartThree();break;
        }
        cout <<"please enter y if you want to repeat and anything else if you want to exit \n";
        cin >> g ;
    }

    return 0;
}
