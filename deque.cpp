/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

/* Constructor for the Deque class */
template <class T>
Deque<T>::Deque(){

/* your code here */
	data.resize(0);
	k1 = -1;
	k2 = -1;

}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T const& newItem)
{
    /**
     * @todo Your code here!
     */
    if(data.size()==0){
    	data.resize(1);
    	data[0] = newItem;
    	k1 = 0;
    	k2 = 0;
    }
    else{
/*
        data.push_back(newItem);
        if((unsigned long)k2 == data.size()-2)
            k2+=1;
        else{
            for(int a=(int)data.size()-2;a>=k2+1;a--){
                data[a+1] = data[a];
            }
            data[k2+1]=newItem;
            k2++;
        }
    }*/
    if(k2 == (int)data.size()-1){
        data.push_back(newItem);
        k2++;
    }
    else{
        data[++k2] = newItem;
    }
    
    }
    //Not sure, if it resize the running time change
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The leftmost item of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    /**
     * @todo Your code here! 
     */

    T left = data[k1];

    k1 += 1;

 /*   printf("\ndataSize: %ld", data.size());
    printf("\nk1: %d", k1);
    printf("\nk2: %d", k2);*/ 

    int real_size = k2-k1+1;
    if(2*real_size<=(int)data.size() && data.size()>=1){
    	vector<T> newData(0);
    	for(int i=k1;i<=k2;i++){
    		newData.push_back(data[i]);
    	}
    	k1=0;
    	k2=newData.size()-1;
    	data = newData;
    }
    else if(data.size()==1){
    	k1 = -1;
    	k2 = -1;
    	data.resize(0);
    }
/*    int real_size = k2-k1+1;
    if(2*real_size<=(int)data.size() && data.size()>1){
        for(int i=0;i<k2-k1+1;i++){
            data[i] = data[k1+i];
        }
        data.resize(k1+k2-1);
        k1=0;
        k2=data.size()-1;
    }
    else if(data.size()==1){
        k1=-1;
        k2=-1;
        data.resize(0);
    }*/
    
    return left;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The rightmost item of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    /**
     * @todo Your code here! 
     */
    T right = data[k2];

    k2-=1;

    //printf("\ndataSize: %ld", data.size());
    //printf("\nk1: %d", k1);
    //printf("\nk2: %d", k2);
    int real_size = k2-k1+1;

    if(2*real_size<=(int)data.size() && data.size()>=1){
    	vector<T> newData(0);
    	for(int i=k1;i<=k2;i++){
    		newData.push_back(data[i]);
    	}
    	k1=0;
    	k2=newData.size()-1;
    	data = newData;
    }
    else if(data.size()==1){
    	k1 = -1;
    	k2 = -1;
    	data.resize(0);
    }
    
    return right;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the left of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    /**
     * @todo Your code here! 
     */
    return data[k1];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    /**
     * @todo Your code here! 
     */
    return data[k2];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    /**
     * @todo Your code here! 
     */
    return (k1==-1);
}
