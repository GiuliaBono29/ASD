import java.util.ArrayList;
import java.util.Hashtable;


public class HeapMinimo<T extends Comparable<T>>{

	ArrayList<T> HEAP = null;

	Hashtable<T, Integer> MAP =null;

	public void add(T VALUE){
		(this.HEAP).add(VALUE);
		MAP.put(VALUE, this.size()-1);
	}  //OK O(1)

	public T get(Integer INDEX){ return (this.HEAP).get(INDEX); }  //OK O(1) Dando un elemento mi ritorna il valore

	public void remove(T VALUE){
		int INDEX=MAP.get(VALUE);
		MAP.remove(VALUE);
		(this.HEAP).remove(INDEX);
	}  //OK O(1)

	public void set(int NEW_INDEX, T VALUE){  //OK O(1)
		(this.HEAP).set(NEW_INDEX, VALUE);
		MAP.replace(VALUE,NEW_INDEX);
	}


	public void newHeap(){						//creazione di un heap minimo vuoto
		this.HEAP = new ArrayList<>();
		this.MAP = new Hashtable<>();

	}  //OK O(1)

	public void insert(T VALUE){		//inserimento di un elemento O(log n)
		int INDEX=this.size();
    	this.add(VALUE);
		while(INDEX>0 && this.get(INDEX).compareTo(this.get(MAP.get(getFather(VALUE))))<0){
			T X = VALUE;
			int INDEX_FATHER = MAP.get(getFather(X));
			this.set(INDEX, this.getFather(VALUE));
			this.set(INDEX_FATHER, X);
			INDEX=INDEX_FATHER;
		}
	}

	public int size(){						//restituzione della dimensione dell'heap (O(1) per definizione di size)
		return (this.HEAP).size();
	} //O(1)

	public T getFather(T VALUE){				//restituzione del padre di un elemento O(1)
		int INDEX = MAP.get(VALUE);
		int INDEX_FATHER=(int)(((float) INDEX/2)-0.5);
		return this.get(INDEX_FATHER);
	}

	public T getLeftSon(T VALUE){			//restituzione del figlio sinistro di un elemento O(1)
		int INDEX=MAP.get(VALUE);
		int INDEX_LEFT_SON=2*INDEX+1;
		if(INDEX_LEFT_SON>this.size()-1){
			return VALUE;
		}
		else{
			return this.get(INDEX_LEFT_SON);
		}
	}

	public T getRightSon(T VALUE){			//restituzione del figlio destro di un elemento O(1)
		int INDEX=MAP.get(VALUE);
		int INDEX_RIGHT_SON=2*INDEX+2;
		if(INDEX_RIGHT_SON>this.size()-1){
			return VALUE;
		}
		else{
			return this.get(INDEX_RIGHT_SON);
		}
	}

	public T extract(){						//estrazione valore minimo O(log n)

		T MIN = null;

		if(this.size()>0){
			T VALUE=this.get(this.size()-1);
			int INDEX=0, INDEX_SON;
			this.remove(VALUE);
			if(this.size()==0){
				return VALUE;
			}
			MIN=HEAP.get(0);
			MAP.remove(get(0));
			MAP.put(VALUE, 0);
			this.set(INDEX,VALUE);
			while(getLeftSon(VALUE).compareTo(VALUE)<0 || getRightSon(VALUE).compareTo(VALUE)<0){
				if(getLeftSon(VALUE).compareTo(getRightSon(VALUE))<0){
					INDEX_SON=MAP.get(getLeftSon(VALUE));
					this.set(INDEX,getLeftSon(VALUE));
					this.set(INDEX_SON,VALUE);
					INDEX=INDEX_SON;
				}
				else{
					INDEX_SON=MAP.get(getRightSon(VALUE));
					this.set(INDEX,getRightSon(VALUE));
					this.set(INDEX_SON,VALUE);
					INDEX=INDEX_SON;
				}
			}
		}
		return MIN;
	}

	public boolean decrese(T OLD_VAL, T NEW_VAL){  //O(n)
		if(OLD_VAL.compareTo(NEW_VAL)>0 /*&& map.get(oldval)!=null*/) {
			int INDEX = MAP.get(OLD_VAL);
			this.set(INDEX, NEW_VAL);
			MAP.remove(OLD_VAL);
			MAP.put(NEW_VAL, INDEX);
			while (INDEX >= 0 && NEW_VAL.compareTo(getFather(NEW_VAL)) < 0) {
				int x = MAP.get(getFather(NEW_VAL));
				this.set(INDEX, getFather(NEW_VAL));
				this.set(x, NEW_VAL);
				INDEX = x;
			}
			return true;
		}
		return false;
	}

	public void print(){  //O(n)
		System.out.println(HEAP);
	}

}