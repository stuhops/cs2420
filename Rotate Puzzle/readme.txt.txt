Stuart Hopkins ~ A02080107

Part 1 - Inefficiencies

	When I first saw this method of solving the puzzle I thought it was very inefficient, hovever, it isn't as bad as I thought.
Yes every level of the tree you travers you go 12^n more boards deep, but the point of the program is to find the absolute best
possible solution for the user to move their board. If we were after one way we might be able to write it better, but to find the best
possible solution this is very close to a necessary program. One big problem I found is that the numbers grew so quickly that if I got
above 5 moves or so I was at risk of overflow in my integer variables. This made the program fail out after testing around 32,000 boards.
There are many issues with this solution, but to find the absolute quickest solution there are not many other ways to find it.

Part 2 - Improvments

	This approach is a very 'stupid' approach. There is no real thinking involved for the computer. The next step in improvment for
this program would be making it 'smarter'. One way that this program is redundant is that even when it moves column 1 north, the very next
level of the tree it moves it south. If we cut this down we could get large improvements. Not enough to really change the big Oh notation, 
but probably enough to make it worth our while.