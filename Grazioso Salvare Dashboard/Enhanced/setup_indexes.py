"""
setup_indexes.py
Author: Freddy Case
Version: 1.0
Date: October 4th, 2026

Purpose:
A one-time setup script that creates the index used by the dashboard's
rescue filters. It uses the admin account because creating an index
changes the database, which lets the dashboard itself stay read-only.
Run once from the terminal: python setup_indexes.py
"""

from dotenv import load_dotenv
from pymongo import MongoClient, ASCENDING
import os

# Load environment variables and set up MongoDB connection using admin credentials
load_dotenv()
username = os.getenv("AAC_ADMIN_USER")
password = os.getenv("AAC_ADMIN_PASS")

if not username or not password:
    raise ValueError("Missing AAC_ADMIN_USER or AAC_ADMIN_PASS in the .env file")

client = MongoClient("localhost", 27017, username=username, password=password)
collection = client["aac"]["animals"]

# Create an index for the rescue filter fields
index_name = collection.create_index(
    [
        ("animal_type", ASCENDING),
        ("sex_upon_outcome", ASCENDING),
        ("breed", ASCENDING),
        ("age_upon_outcome_in_weeks", ASCENDING),
    ],
    name="rescue_filter_index",
)
print("Created index:", index_name)