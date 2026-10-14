public class Arc<N, A> {
    private N NODE1;
    private N NODE2;
    private A VALUE;

    private boolean DIRECT;

    public Arc(N NODE1, N NODE2, A VALUE, boolean DIRECT) {
        this.NODE1 = NODE1;
        this.NODE2 = NODE2;
        this.VALUE = VALUE;
        this.DIRECT = DIRECT;
    }

    public Arc(N NODE1, N NODE2, boolean DIRECT) {
        this.NODE1 = NODE1;
        this.NODE2 = NODE2;
        this.DIRECT = DIRECT;
    }

    public N getNode1() {
        return NODE1;
    }

    public void setNode1(N NODE1) {
        this.NODE1 = NODE1;
    }

    public N getNode2() {
        return NODE2;
    }

    public void setNode2(N NODE2) {
        this.NODE2 = NODE2;
    }

    public A getValue() {
        return VALUE;
    }

    public void setValue(A VALUE) {
        this.VALUE = VALUE;
    }

    public boolean isDirect() {
        return DIRECT;
    }

    public void setDirect(boolean DIRECT) {
        this.DIRECT = DIRECT;
    }

    @Override
    public int hashCode() {
        final int PRIME = 31;
        int RESULT = 1;

        if (DIRECT) {
            RESULT = PRIME * RESULT + ((NODE2 == null) ? 0 : NODE2.hashCode());
            RESULT = PRIME * RESULT + ((NODE1 == null) ? 0 : NODE1.hashCode());
        }
        else{
            RESULT = PRIME * RESULT + (((NODE2 == null) ? 0 : NODE2.hashCode()) + ((NODE1 == null) ? 0 : NODE1.hashCode()));
        }

        return RESULT;
    }

    @Override
    @SuppressWarnings("unchecked")
    public boolean equals(Object OBJ) {
        if ((OBJ == null) || !(OBJ instanceof Arc)){
            return false;
        }
        Arc EDGE = (Arc) OBJ;

        return this.NODE1.equals(EDGE.NODE1) &&
                this.NODE2.equals(EDGE.NODE2) ||
                (!DIRECT && this.NODE1.equals(EDGE.NODE2) && this.NODE2.equals(EDGE.NODE1));
    }

    @Override
    public String toString() {
        return "Edge [src=" + NODE1 + ", label=" + VALUE + ", dest=" + NODE2 + "]";
    }

}
