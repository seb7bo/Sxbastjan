# Singleton

Singleton is a creational design pattern that lets you ensure that a class has only one instance, while providing a global access point to this instance.

## Problem

The Singleton pattern solves two problems at the same time, violating the Single Responsability Principle.

1. Ensure that a class has just a single instance.Why would anyone wnat to control how many instances a class has? The most common reason for this is to control access to some share resource- for example a data base or a file.

Here's how it works: imagen that you created an object but after a while decided to create a new one. Instead of receivinf a fresh object, you'll get the one you already created.

Note that this behavior is impossible to implement with a regular contructor since a constructor call must always return a new object by desing.