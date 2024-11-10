# Distributed Key-Value Store

The goal of this project is to try to implement a distributed key-value store. Ideally, it should provide a scalable, fault-tolerant, and highly available solution for storing and retrieving key-value pairs. 

## Why?

- Interesting: I happen to also attend a Principles of Distributed Systems class, so it's an opportunity to tie two subjects together, try to implement learned concepts.
- Techinically challenging enough.
- Flexible: in my past projects I struggled to choose the right scope, so the projects "is not for 1 week, but not for half a year" - it was hard to think of a features to add/remove, because the topic was very concrete. Here, I can be a bit more flexible along the way: 

## Logic-related features
- Nodes (and client) can interact with the system through HTTP APIs.
- Data replication.
- Data Partitioning (consistent hashing).
- Fault detection: health checks (either some cental system responsible for it, or gossip protocols).
- Data consistency (RAFT or Paxos).
- Communication between nodes over HTTP APIs.

## Project-related features
- Testing: don't forget about integration tests to ensure code works; include non-trivial cases.
- Performance benchmarks.

## Inspiration/references
- Source of the idea was [Amazon Dynamo paper](https://www.allthingsdistributed.com/files/amazon-dynamo-sosp2007.pdf).
- [Article about consistent hashing](https://arpitbhayani.me/blogs/consistent-hashing/).
- Principy distribuovaných systémů [NSWI035](https://www.ksi.mff.cuni.cz/teaching/nswi035-web/).
- [RAFT paper](https://raft.github.io/raft.pdf).