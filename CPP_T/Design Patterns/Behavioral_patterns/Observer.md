# Observer

Also known as: Event Subscriber, Listerner

## Intent

Observer is a behavioral design pattern that lets you define a subscription mechanism to notify mutiple objects about any events that happen to the object they´re observing.

## Problem

Imagine that you have two types of objects: a Customer and Store. The customer is very interested in a particular brand of product(say , it´s new model of the iPhone) which should become available in the store very soon.

The customer could visit the store every day and chech product availability. But while the product is still in route, most of these trips would be pointless.

On the other hand, the store could send tons of emails(which might be consider spam)to all customers each time a new product becomes available. This wold save some soctumers form endless trips to the store.At the same time, it´d upset other costumer who aren´t interested in new products.

It looks like we´ve got a conflict. Either customer wastes time checking product availability ir the store wastes resources notifying the wrong costumers.

## Solution

