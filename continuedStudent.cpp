#include "continued.h"
unsigned int gcd(unsigned int a, unsigned int b){
    if(b==0){
        return a;
    }
    else{
        return gcd(b,a%b);
    }
    
    return 0;
}
unsigned int gcdFaster(unsigned int a, unsigned int b){
    
    
    int c;
    while (a != b) {
        while (a > b) {
            c = a - b;
            a = c;
        }
        while (b > a) {
            c = b - a;
            b = c;
        }
    }
    return a;
    
}
//takes two fractions and adds the econd on to he nd of the other
void addLast(ContinuedFraction* x, ContinuedFraction*y ){

    while (x->tail!=NULL) {
        x= x->tail;
    }
    x->tail = y;
}
//preforms a copy that uses all elements in the list
ContinuedFraction *deepCopy(ContinuedFraction* x )
{
    ContinuedFraction* Hcopy = new ContinuedFraction;
    Hcopy->head = x->head;
    
    while (x->tail != NULL)
    {
        
        ContinuedFraction* copy = new ContinuedFraction;
        copy->head = x->head;
        addLast(Hcopy,copy);
        x = x->tail;
            
        
    }
    return Hcopy;
   
}


ContinuedFraction *getCFlargerThanOne(unsigned int b, unsigned int a) {
    double x =(double)b/(double)a;
    
    if((int)x <1){
        return NULL;
    }
    ContinuedFraction *result ;
    result = (ContinuedFraction*) malloc (sizeof(ContinuedFraction));
    
    result->head= (int)x;
    
    return result;
}

ContinuedFraction *getCF(unsigned int b, unsigned int a) {
    
    ContinuedFraction *x = new ContinuedFraction;
    x->head = 0;
    //generate first part of cf
    x->tail= getCFlargerThanOne(b, a);
    //keep track of this becusethis is what we ultamitly return.
    ContinuedFraction *head = x->tail;
    while (x->tail != NULL) {
        //address the next part of the fraction
        x = x->tail;
        //get remainder
        int r  = b % a;
        //debug ;)
        //swap old denomnator for numerator
        b=a;
        //replace old denmoenator with the remander
        a = r;
        //calculate continued fraction and asign it to the next part of the cf object, like
        //a linked list
        ContinuedFraction *y = getCFlargerThanOne(b, a);
        x->tail = y;
    }
    return head;
}


ContinuedFraction *getCF(unsigned int head, ContinuedFraction *fixed, ContinuedFraction *period) {
    //creates fraction and gives it head the one passed from the func and gives its tail ficed
    ContinuedFraction *x = new ContinuedFraction;
    x->head= head;
    x->tail = fixed;
    //speffically coppies the fraction--Deep Copy
    ContinuedFraction *copy;
    copy = deepCopy(period);
    
    ContinuedFraction *temp = copy;
    while (temp->tail != NULL) {
        temp = temp->tail;
    }
    //puts period at end
    temp->tail = copy;
    //respeifies x
    temp= x;
    while (temp->tail != NULL) {
        temp = temp->tail;
    }
    temp->tail = copy;
    
    return x;
}



Fraction getApproximationReccursive(ContinuedFraction *fr, unsigned int n) {
    Fraction *f = new Fraction();
    Fraction *fp = new Fraction();
    int de;
    int num;
    //basecase
    if (n==0 || fr->tail==nullptr){
        f->numerator = 1;
        f->denominator = fr->head;
        return *f;
    }
    //else
    f->numerator = 1;
    //recursive step
    *fp = getApproximationReccursive(fr->tail, n--);
    //save values
    de = fp->denominator;
    num = fp->numerator;
    //multiplies the numerator by the head and then adds the sumation of the contained fractions"num"
    fp->denominator = num+(fr->head * fp->denominator);
    fp->numerator = de;

    return *fp;
}


Fraction getApproximation(ContinuedFraction *fr, unsigned int n) {
    Fraction *fp = new Fraction();
    //plugs into recurse
    *fp = getApproximationReccursive(fr->tail, n-=1);
    //takes multiplies it by the denominator and adds it to the summation
    fp->numerator = (fr->head * fp->denominator)+fp->numerator;
    
    return *fp;
}


