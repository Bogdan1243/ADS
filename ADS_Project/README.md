Festival Flow — Music Festival Stage & Artist Manager

Overview

Festival Flow is a browser-based web application built to demonstrate the practical application
of advanced data structures in a real-world scheduling context. The application simulates a
music festival management system where organizers can add artists, assign them to stages,
adjust their performance slots, and search through the lineup — all while visualizing the
underlying data structures updating in real time.

The project was developed as part of the ADS Course and implements four data structures
from scratch: a Fibonacci Heap, a Red-Black Tree, a Disjoint Set (Union-Find), and the
KMP String Matching algorithm.


Data Structures

1. Fibonacci Heap
The Fibonacci Heap serves as the core performance queue. Artists are inserted with a
priority value between 1 and 10, where 1 represents the highest-priority slot (headliner).
The heap always surfaces the artist with the lowest priority number as the next to perform.

The key advantage of using a Fibonacci Heap over a simpler structure like a binary heap is
the O(1) amortized cost of the decrease-key operation. In a festival context, this maps
directly to promoting an artist to an earlier slot without rebuilding the entire queue.

Key operations and their complexities:
- insert(artist): O(1) amortized
- extractMin(): O(log n) amortized
- decreaseKey(node, newPriority): O(1) amortized
- remove(node): O(log n) amortized

The heap is visualized as a forest of trees using SVG, where each node displays
the artist name and their current slot number.

2. Red-Black Tree
The Red-Black Tree acts as the master artist registry. Every artist admitted into the
system is stored in the tree, indexed by a unique numeric ID. Because the tree is
self-balancing, search, insertion, and deletion are all guaranteed to run in O(log n)
time regardless of insertion order, avoiding the worst-case linear time of an
unbalanced BST.

Key operations:
- insert(artist): O(log n)
- delete(id): O(log n)
- search(id): O(log n)

The tree is visualized as a node-edge diagram where each node is colored red or black
according to the balancing rules, and displays the artist name alongside their
current priority slot.

3. Disjoint Sets (Union-Find)
The Disjoint Set structure manages stage assignments. Each artist belongs to exactly
one stage (Main Stage, Electronic, Acoustic, or Emerging), represented as a set.
The structure supports two optimizations: path compression in the find operation and
union by rank, which together bring the amortized cost of both operations to nearly O(1)
(inverse Ackermann time complexity).

In the application, the union operation is used to simulate stage merges — for example,
when a stage is cancelled and its artists are reassigned to another.

Key operations:
- makeSet(id): O(1)
- find(id): O(alpha(n)) amortized with path compression
- union(id1, id2): O(alpha(n)) amortized with union by rank

Artists are displayed as color-coded clusters grouped by their current stage representative.

4. KMP String Matching
The Knuth-Morris-Pratt algorithm is used to power the search functionality. When a user
types a query, KMP runs against every artist name and genre string in the registry,
returning the positions of all matches. Unlike naive substring search which runs in O(n*m),
KMP constructs a failure function from the pattern in O(m) time and uses it to scan the
text in O(n) time, making it significantly more efficient for repeated queries over a
large roster.

The search panel displays the failure function table alongside highlighted match positions
in the results, making the inner workings of the algorithm visible.

Application Features
- Dashboard: Displays total artist count, distribution per stage, and the next
  artist scheduled to perform.
- Add Artist: Inserts a new artist into all three data structures simultaneously.
- Next Performance: Calls extractMin() on the Fibonacci Heap and removes the artist
  from the registry and stage cluster.
- Promote Artist: Adjusts an artist's slot using decreaseKey() (for promotions)
  or remove() followed by insert() (for demotions).
- Search: Runs KMP matching in real time and highlights results.
- Visualizer: Dedicated panel showing live SVG diagrams of all four structures.

---

How to Run

Open `index.html` directly in any modern browser. No installation or build step is required.

Alternatively, serve it locally with:

    npx serve .

---

File Structure

    index.html   — Complete application: markup, styles, data structure implementations,
                   and React components in a single self-contained file.
    README.md    — This documentation.