"""
CRUD_Python_Module.py
Author: Freddy Case
Version: 2.0
Date: October 4th, 2026
Original: CS 340, December 2025

Purpose:
Create, read, update, and delete (CRUD) operations for the AAC animal
shelter MongoDB collection, used by the Grazioso Salvare dashboard.

Changes in version 2.0 (CS 499 enhancement):
- Removed the hardcoded database credentials. Credentials are now loaded
  from a .env file by the code that uses this module to make it more secure.
- Database errors are caught with PyMongoError and the error reason is printed.
  Now, permissions problem can be told apart from a connection problem.
- Added get_breed_counts() for efficiency. get_breed_counts() uses an
  aggregation pipeline instead of sending every record to pandas.
"""

from pymongo import MongoClient 
from bson.objectid import ObjectId 
from pymongo.errors import PyMongoError

class AnimalShelter(object): 
    """ CRUD operations for Animal collection in MongoDB """ 

    def __init__(self, username, password): 
        # Initializing the MongoClient. This helps to access the MongoDB 
        # databases and collections. This is hard-wired to use the aac 
        # database, the animals collection, and the aac user. 
        # 
        # You must edit the password below for your environment. 
        # 
        # Connection Variables 
        #  
        HOST = 'localhost' 
        PORT = 27017 
        DB = 'aac' 
        COL = 'animals' 
        
        # Build the Mongo URI using the provided credentials
        mongo_uri = "mongodb://%s:%s@%s:%d" % (username, password, HOST, PORT)
        
        # 
        # Initialize Connection 
        # 
        self.client = MongoClient(mongo_uri)
        self.database = self.client['%s' % (DB)] 
        self.collection = self.database['%s' % (COL)] 

    # Create a method to return the next available record number for use in the create method
    """
        Returns the next available record number.
        referencing https://www.mongodb.com/docs/languages/python/pymongo-driver/current/crud/query/count/
    """
    def get_next_record_number(self):
        count = self.collection.count_documents({})
        return count + 1
        
    # Complete this create method to implement the C in CRUD. 
    """
        Insert a new document into the animals collection.
        referencing https://www.mongodb.com/docs/languages/python/pymongo-driver/current/crud/insert/
    """
    def create(self, data):
        if data is not None:
            #if works, returns True
            try:
                result = self.database.animals.insert_one(data)  # data should be dictionary    
                return True
            # Catch any database errors and report the reason.
            except PyMongoError as error:
                print(f"Create failed: {error}")
                return False
        else: 
            raise Exception("Nothing to save, because data parameter is empty") 

    # Create method to implement the R in CRUD.
    """
        Read documents from the animals collection using find().
        referencing https://www.mongodb.com/docs/languages/python/pymongo-driver/current/crud/query/find/
    """
    def read(self, query):
        if query is not None:
            cursor = self.database.animals.find(query)
            #return result is in a list
            return list(cursor)
        else:
            #returns empty list when unsucessful
            return[]
        
    # Update method to implement the U in CRUD.
    """
        Update document(s) in the animals collection using update_many().
        referencing https://www.mongodb.com/docs/languages/python/pymongo-driver/current/crud/update/
    """
    def update(self, query, new_values):
        if query is not None:
            try:
                # apply $set to modify matching documents
                result = self.collection.update_many(query, {"$set": new_values})
                # return number of modified documents
                return result.modified_count
            except PyMongoError as error:
                # report why the update failed
                print(f"Update failed: {error}")
                return 0
        else:
            raise Exception("Query parameter is empty")
        
        
    # Delete method to implement the D in CRUD.
    """
        Delete document(s) from the animals collection using delete_many().
        referencing https://www.mongodb.com/docs/languages/python/pymongo-driver/current/crud/delete/
    """
    def delete(self, query):
        if query is not None:
            try:
                # delete all documents matching the query
                result = self.collection.delete_many(query)
                # return number of deleted documents
                return result.deleted_count
            except PyMongoError as error:
                print(f"Delete failed: {error}")
                return 0
        else:
            raise Exception("Query parameter is empty")

    # Aggregation pipeline method to get breed counts
    # Get breed counts method to implement a read operation for breed statistics.
    def get_breed_counts(self, query, limit=10):
        """
        Counts animals per breed inside MongoDB and returns only the
        top results, instead of sending every record to Python to count.
        """
        pipeline = [
            # keep only the animals that match the current filter
            {"$match": query},
            # group by breed and count how many animals are in each group
            {"$group": {"_id": "$breed", "count": {"$sum": 1}}},
            # largest groups first
            {"$sort": {"count": -1}},
            # only send back the top breeds
            {"$limit": limit},
        ]
        try:
            return list(self.collection.aggregate(pipeline))
        except PyMongoError as error:
            print(f"Breed count failed: {error}")
            return []

        