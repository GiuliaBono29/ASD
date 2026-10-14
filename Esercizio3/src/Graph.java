import java.util.*;
import java.util.Map;

public class Graph<N extends Comparable<N>, A extends Comparable<A>> {

    private Boolean DIRECT;

    private Hashtable<N, ArrayList<Node<N,A>>> NODES=null;

    private HashSet<Arc<N,A>> EDGE;


    public Graph(boolean DIRECT) {  //O(1) creazione di un grafo vuoto
        this.NODES=new Hashtable<N, ArrayList<Node<N, A>>>();
        this.EDGE= new HashSet<Arc<N, A>>();
        this.DIRECT=DIRECT;
    }

    public void insertNode(N ETICHETTA){    //O(1) aggiunta di un nodo HashTable(String: "A", Node: ["A", null])

        if (ETICHETTA != null){
            if(!NODES.containsKey(ETICHETTA)) {
                NODES.put(ETICHETTA, new ArrayList<Node<N, A>>());
            }
        }
    }

    public void insertArc(N NODE1, N NODE2, A LABEL){  //O(1) aggiunta di un arco

        NODES.get(NODE1).add(new Node<N,A>(NODE2, LABEL));
        if (!isDirect()) {
            NODES.get(NODE2).add(new Node<N, A>(NODE1, LABEL));
        }
        EDGE.add(new Arc<N,A>(NODE1, NODE2, LABEL, isDirect()));
    }


    public boolean isDirect(){  //O(1) verifica se il grafo è vuoto
        if(DIRECT){
            return true;
        }
        else{
            return false;
        }
    }

    public boolean containNode(N NODE){    //O(1) verifica se il grafo contiene un dato nodo
        if(NODES.containsKey(NODE)){
            return true;
        }
        else{
            return false;
        }
    }

    public boolean containArc(N NODE1, N NODE2){    //O(1) verifica se il grafo contiene un dato arco
        if(containNode(NODE1) && containNode(NODE2)){
            return EDGE.contains(new Arc<N, A>(NODE1, NODE2, isDirect()));
        }
        return false;
    }

    public void removeNode(N NODE) {   //O(n)

        NODES.remove(NODE);

        for(Map.Entry<N, ArrayList<Node<N, A>>> entry : NODES.entrySet()){
            entry.getValue().remove(new Node(NODE));
        }

        for(Iterator<Arc<N, A>> i = EDGE.iterator(); i.hasNext();){
            Arc e = i.next();
            if (e.getNode1().equals(NODE) || e.getNode2().equals(NODE)){
                i.remove();
            }
        }

    }

    public void removeArc(N NODE1, N NODE2){    //O(1) cancellazione di un arco

        NODES.get(NODE1).remove(new Node<N, A>(NODE2));

        if(!isDirect()){
            NODES.get(NODE2).remove(new Node<N, A>(NODE1));
        }

        EDGE.remove(new Arc<N, A>(NODE1,NODE2,this.isDirect()));
    }

    public int nodesNum(){  //O(1) ritorna numero di nodi presenti
        return NODES.size();
    }

    public int arcsNum(){   //O(n) ritorna il numero di archi presenti
        return EDGE.size();
    }

    public Set<N> returnNodes(){   //O(n) ritorna l'elenco dei nodi
        return NODES.keySet();
    }

    public HashSet<Arc<N, A>> returnArc() {
        return EDGE;
    }

    public ArrayList<Node<N, A>> returnNodesAdj(N NODE){
        return NODES.get(NODE);
    }

    public A ReturnArcLabel(N NODE1, N NODE2){

        A LABEL = null;

        for(Node<N, A> e : NODES.get(NODE1)){
            if(e.getElem().equals(NODE2)){
                LABEL = e.getLabel();
            }
        }

        return LABEL;
    }

}

