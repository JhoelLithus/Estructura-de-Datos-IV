
template <class T>
FibonacciHeap<T>::FibonacciHeap()
{
	heap=_empty();
}

template <class T>
FibonacciHeap<T>::~FibonacciHeap() 
{
	if(heap) 
	{
		_deleteAll(heap);
	}
}
	
template <class T>
node<T>* FibonacciHeap<T>:: insert(T value)
{
	node<T>* ret=_singleton(value);
	heap=_merge(heap,ret);
	return ret;
}
	
template <class T>
void FibonacciHeap<T>:: merge(FibonacciHeap& other) 
{
	heap=_merge(heap,other.heap);
	other.heap=_empty();
}
	
template <class T>
bool FibonacciHeap<T>::isEmpty() 
{
	return heap==NULL;
}


template <class T>
T FibonacciHeap<T>::getMinimum() 
{
	return heap->value;
}

template <class T>
T FibonacciHeap<T>::removeMinimum() 
{
	node<T>* old=heap;
	heap=_removeMinimum(heap);
	T ret=old->value;
	delete old;
	return ret;
}
	
template <class T>
void FibonacciHeap<T>::decreaseKey(node<T>* n,T value) 
{
	heap=_decreaseKey(heap,n,value);
}
	
template <class T>
node<T>* FibonacciHeap<T>::find(T value) 
{
	return _find(heap,value);
}

template <class T>
node<T>* FibonacciHeap<T>:: _empty() 
{
	return NULL;
}
	
template <class T>
node<T>* FibonacciHeap<T>::_singleton(T value) 
{
	node<T>* n=new node<T>;
	n->value=value;
	n->prev=n->next=n;
	n->degree=0;
	n->marked=false;
	n->child=NULL;
	n->parent=NULL;
	return n;
}
	
template <class T>
node<T>* FibonacciHeap<T>::_merge(node<T>* a,node<T>* b)
{
	if(a==NULL)return b;
	if(b==NULL)return a;
	if(a->value>b->value) 
	{
		node<T>* temp=a;
		a=b;
		b=temp;
	}
	node<T>* an=a->next;
	node<T>* bp=b->prev;
	a->next=b;
	b->prev=a;
	an->prev=bp;
	bp->next=an;
	return a;
}	
	
template <class T>
void FibonacciHeap<T>:: _deleteAll(node<T>* n) 
{
	if(n!=NULL) 
	{
		node<T>* c=n;
		do 
		{
			node<T>* d=c;
			c=c->next;
			_deleteAll(d->child);
			delete d;
		} 
		while(c!=n);
	}
}
	
template <class T>
void FibonacciHeap<T>::_addChild(node<T>* parent,node<T>* child) 
{
	child->prev=child->next=child;
	child->parent=parent;
	parent->degree++;
	parent->child=_merge(parent->child,child);
}
	
template <class T>
void FibonacciHeap<T>::_unMarkAndUnParentAll(node<T>* n) 
{
	if(n==NULL)return;
	node<T>* c=n;
	do 
	{
		c->marked=false;
		c->parent=NULL;
		c=c->next;
	}
	while(c!=n);
}
		
template <class T>
node<T>* FibonacciHeap<T>::_removeMinimum(node<T>* n) 
{
	_unMarkAndUnParentAll(n->child);
	if(n->next==n) 
	{
		n=n->child;
	} 
	else 
	{
		n->next->prev=n->prev;
		n->prev->next=n->next;
		n=_merge(n->next,n->child);
	}
	if(n==NULL)return n;
	node<T>* trees[64]={NULL};
	
	while(true) 
	{
		if(trees[n->degree]!=NULL) 
		{
			node<T>* t=trees[n->degree];
			if(t==n)break;
			trees[n->degree]=NULL;
			if(n->value<t->value) 
			{
				t->prev->next=t->next;
				t->next->prev=t->prev;
				_addChild(n,t);
			} 
			else 
			{
				t->prev->next=t->next;
				t->next->prev=t->prev;
				
				if(n->next==n) 
				{
					t->next=t->prev=t;
					_addChild(t,n);
					n=t;
				} 
				
				else 
				{
					n->prev->next=t;
					n->next->prev=t;
					t->next=n->next;
					t->prev=n->prev;
					_addChild(t,n);
					n=t;
				}
			}
			continue;
		} 
		else 
		{
			trees[n->degree]=n;
		}
		n=n->next;
	}
	node<T>* min=n;
	node<T>* start=n;
	do 
	{
		if(n->value<min->value)min=n;
		n=n->next;
	} 
	while(n!=start);
		return min;
}
	
	
template <class T>
node<T>* FibonacciHeap<T>::_cut(node<T>* heap,node<T>* n) 
{
	if(n->next==n) 
	{
		n->parent->child=NULL;
	} 
	else 
	{
		n->next->prev=n->prev;
		n->prev->next=n->next;
		n->parent->child=n->next;
	}
	n->next=n->prev=n;
	n->marked=false;
	return _merge(heap,n);
}
	
	
template <class T>
node<T>* FibonacciHeap<T>::_decreaseKey(node<T>* heap,node<T>* n, T value) 
{
	if(n->value<value)return heap;
	n->value=value;
	if(n->parent) 
	{
		if(n->value<n->parent->value) 
		{
			heap=_cut(heap,n);
			node<T>* parent=n->parent;
			n->parent=NULL;
			while(parent!=NULL && parent->marked) 
			{
				heap=_cut(heap,parent);
				n=parent;
				parent=n->parent;
				n->parent=NULL;
			}
			if(parent!=NULL && parent->parent!=NULL)parent->marked=true;
		}
	} 
	else
	 {
		if(n->value < heap->value) 
		{
			heap = n;
		}
	}
	return heap;
}

template <class T>
node<T>* FibonacciHeap<T>::_find(node<T>* heap,T value) 
{
	node<T>* n=heap;
	if(n==NULL)return NULL;
	do 
	{
		if(n->value==value)return n;
		node<T>* ret=_find(n->child,value);
		if(ret)return ret;
		n=n->next;
	}
	while(n!=heap);
		return NULL;
}
/*	
template <class T>
void FibonacciHeap<T>:: printArbol(int num)
{
    string num_arch = to_string(num);
    string ext1 = ".dot";
    string num_xt1=""+ num_arch +""+ ext1 +"";
    ofstream os(num_xt1);

    string s = to_string(num);
    string pt1="dot.exe -Tpng  < ";
    string pt2=" > ";
    string pt3=".png";
    string rt=""+ pt1 +""+ num_xt1 +""+ pt2 +""+ s +""+ pt3 +"";
    const char *buffer = rt.c_str();

    os<<"graph {"<<endl;
    os<<root->key<<endl;
    printArbol(os,root);
    os<<"}"<<endl;
    os.close();
    system(buffer);
}


template <class T>
void FibonacciHeap<T>::printArbol(ofstream & os, node<T> *n)
{
    if(n!=NULL)
    {    
        if(n->p_children[0]!=NULL)
		{
            os<<n->key;
            os<<"--";
            os<<n->p_children[0]->key<<endl;
            printArbol(os,n->p_children[0]);
        }
        if(n->p_children[1]!=NULL)
		{
            os<<n->key;
            os<<"--";
            os<<n->p_children[1]->key<<endl;
            printArbol(os,n->p_children[1]);
        }
    }
}
*/	
