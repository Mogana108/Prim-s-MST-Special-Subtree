#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int N, M;
int S = 0;
int graph[3001][3001];
long long sum = 0;
int visited_nodes[3001] = { 0 };
int no_visited_nodes = 0;

typedef struct {
    int len;
    short s;
    short e;
} vertex;

vertex vertex_heap[3001*3001];
int next_heap_index = 1;

int is_heap_empty()
{
    return (next_heap_index == 1);
}

void push_to_heap(vertex v)
{
    int i = next_heap_index;
    vertex_heap[i] = v;
    while(i > 1 && vertex_heap[i/2].len > vertex_heap[i].len)
    {
        vertex tmp = vertex_heap[i/2];
        vertex_heap[i/2] = vertex_heap[i];
        vertex_heap[i] = tmp;
        i /= 2; 
    }
    
    next_heap_index++;
}

vertex pop_from_heap()
{
    vertex ret = vertex_heap[1];
    vertex lower_elem = vertex_heap[next_heap_index-1];
    next_heap_index--;
    
    int i = 1;
        
    vertex_heap[i] = lower_elem;
    while(i < next_heap_index)
    {
        int li = 2*i;
        int ri = 2*i+1;
        int ex_index = 0;

        if(li < next_heap_index)
        {
            if(vertex_heap[li].len < vertex_heap[i].len)
            {
                ex_index = li;
            }
            
        }
        
        if(ri < next_heap_index)
        {
            if(vertex_heap[ri].len < vertex_heap[i].len &&
               (!ex_index || vertex_heap[ri].len < vertex_heap[li].len))
            {
                ex_index = ri;
            }
        }
        
        if(ex_index)
        {
            vertex tmp = vertex_heap[i];
            vertex_heap[i] = vertex_heap[ex_index];
            vertex_heap[ex_index] = tmp;
            i = ex_index;
        }
        else break;
    }
    
    return ret;
}

void push_all_vertex_edges(int s)
{
  //  printf("All edges for : %d\n", s);
    for(int e = 1; e <= N; e++)
    {
        if(graph[s][e] != -1)
        {
            vertex v = { graph[s][e], s, e};
      //      printf("Pushing %d-%d (len: %d)\n", s, e, graph[s][e]);
            push_to_heap(v);
        }
    }
}


int main() {
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            graph[i][j] = -1;
        
    for(int i = 1; i <= M; i++)
    {
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        graph[i][j] = k;    
        graph[j][i] = k;    
    }
    
    scanf("%d", &S);
    no_visited_nodes = 1;
    visited_nodes[S] = 1;
   //         printf("Visited node 1\n");
    push_all_vertex_edges(S);
    
    while(no_visited_nodes < N)
    {
        vertex v = pop_from_heap();
        if(visited_nodes[v.e] == 0)
        {
            visited_nodes[v.e] = 1;
          //  printf("Visited node %d\n", v.e);
            no_visited_nodes++;
            push_all_vertex_edges(v.e);
           // printf("! %d-%d (len: %d)\n", v.s, v.e, v.len);
            sum += v.len;
        }
    }
    
    printf("%lld\n", sum);
        
    return 0;
}
