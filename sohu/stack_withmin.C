typedef struct NewStack{
	stack s1, s2;
}NewStack;


PUSH(S, e)
S.s1.push(e)
if EMPTY(S.s2)
	then S.s2.push(e)
	else if e < S.s2.top()
	then S.s2.push(e)

POP(S)
e <- S.s1.pop()
if e = S.s2.top()
	then S.s2.pop()
return e

MINIMUM(S)
return S.s2.top()

