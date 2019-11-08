import networkx as nx
import itertools as it
from networkx.algorithms import bipartite
from networkx.algorithms.planarity import check_planarity
import matplotlib.pyplot as plt
from collections import defaultdict

graph = defaultdict(list) 
net_graph = nx.Graph()

def draw_graph(nodes, g, name):
    nx.draw(g, with_labels = True) 
    plt.savefig(name+".png")
    plt.clf()

def draw_planar_graph(nodes, g, name):
    nx.draw_planar(g, with_labels = True) 
    plt.savefig(name+".png")
    plt.clf()

def get_graph(nodes, graph):    
    nodes = int(nodes)
    for i in range(0, nodes):
        net_graph.add_node(i+1)

    for node in graph:
        for neighbour in graph[node]:
            node = int(node)
            neighbour = int(neighbour)
            net_graph.add_edge(node, neighbour)

def is_connected(graph):
    if nx.is_connected(graph):
        return True
    else:
        return False

def addEdge(graph,u,v): 
    graph[u].append(v)
    graph[v].append(u) 

def deleteVertex(graph, u):
    for v in graph.values():
        if u in v:
            v.remove(u)
    graph.pop(u, None)
    u = int(u)
    net_graph.remove_node(u)

def is_planar(G):
    return check_planarity(G)[0]

    result=True
    bad_minor=[]
    n=len(G.nodes())
    if n>5:
        for subnodes in it.combinations(G.nodes(),6):
            subG=G.subgraph(subnodes)
            if bipartite.is_bipartite(G):
                X, Y = bipartite.sets(G)
                if len(X)==3:
                    result=False
                    bad_minor=subnodes
    if n>4 and result:
        for subnodes in it.combinations(G.nodes(),5):
            subG=G.subgraph(subnodes)
            if len(subG.edges())==10:
                result=False
                bad_minor=subnodes
    return result

def planarity(G):
    return check_planarity(G)

def graph_valid(graph):
    for key, value in graph.items():
        print(key, value)
        node_degree = len([item for item in value if item])
        if node_degree > 3:
            return False
    return True

######  Main Function  ######

if __name__=='__main__':
    nodes = input("Enter the number of nodes: ")

    edges = input("Enter the number of edges: ")
    edges = int(edges)

    for i in range(0, edges):
        src = input("Enter the source node: ")
        des = input("Enter the destination node: ")
        addEdge(graph, src, des)

    get_graph(nodes, graph)
    print("\n")
    is_connected(net_graph)

    draw_graph(nodes, net_graph, "Original_Graph")

    # if not graph_valid(graph):
    #     print("Graph over degree 3 are not allowed")
    #     exit()

    if is_planar(net_graph):
        print("It is planar")
        draw_planar_graph(nodes, net_graph, "Planar_Graph")
    else:
        print("It is non planar")
        i = 1
        while (not is_planar(net_graph) and i<=int(nodes)):
            net_graph_copy = net_graph.copy()
            net_graph_copy.remove_node(i)
            if is_connected(net_graph_copy):
                print("We removed vertex number "+ str(i))
                net_graph.remove_node(i)
                i = i+1
            else:
                i = i+1
                continue
        if is_planar(net_graph):
            print("It is planar")
            draw_planar_graph(nodes, net_graph, "Planar_Graph")
        else:
            print("It is non planar")
