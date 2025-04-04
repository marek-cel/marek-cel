import psycopg2

print("Connecting to the database...")
conn = psycopg2.connect(
    host="0.0.0.0",
    database="dbname",
    user="user",
    password="pass"
)

cur = conn.cursor()

# Run a query
cur.execute("SELECT * FROM contacts")

# Fetch and display results
rows = cur.fetchall()
for row in rows:
    print(row)

# Cleanup
cur.close()
conn.close()
