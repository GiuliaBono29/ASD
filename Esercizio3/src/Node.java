
public class Node<N extends Comparable<N>, A extends Comparable<A>> implements Comparable<Node<N, A>>{
    private N ELEMENT;
    private A LABEL;

    public Node(N ELEMENT, A LABEL) {
        this.ELEMENT = ELEMENT;
        this.LABEL = LABEL;
    }

    public Node(N ELEMENT) {
        this.ELEMENT = ELEMENT;
    }

    public N getElem() {
        return ELEMENT;
    }

    public void setElem(N ELEMENT) {
        this.ELEMENT = ELEMENT;
    }

    public A getLabel() {
        return LABEL;
    }

    public void setLabel(A LABEL) {
        this.LABEL = LABEL;
    }

    @Override
    public int hashCode() {
        final int PRIME = 31;
        int RESULT = 1;
        RESULT = PRIME * RESULT + ((ELEMENT == null) ? 0 : ELEMENT.hashCode());
        return RESULT;
    }

    @Override
    @SuppressWarnings("unchecked")
    public boolean equals(Object OBJ) {
        if((OBJ==null)||!(OBJ instanceof Node/*<?,?>*/)){
            return false;
        }
        Node NODO = (Node/*<E,G>*/) OBJ;
        return this.ELEMENT.equals(NODO.ELEMENT);
    }

    @Override
    public String toString() {
        return "Node [elem=" + ELEMENT + ", label=" + LABEL + "]";
    }

    @Override
    public int compareTo(Node<N, A> OBJ) {
        return LABEL.compareTo(OBJ.LABEL);
    }
}
