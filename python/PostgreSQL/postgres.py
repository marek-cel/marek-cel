import psycopg2

print("Connecting to the database...")
conn = psycopg2.connect(
    host="0.0.0.0",
    database="dbname",
    user="user",
    password="pass"
)

cursor = conn.cursor()

cursor.execute("SELECT * FROM contacts")
rows = cursor.fetchall()
print("Fetching data...")
for row in rows:
    print(row)


# export the data to a CSV file
with open('contacts.csv', 'w') as f:
    cursor.copy_expert("COPY contacts TO STDOUT WITH CSV HEADER", f)

print("Closing the connection...")
conn.close()
