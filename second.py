import pymysql
conn = pymysql.connect(host='127.0.0.1', user='Jiahao', passwd='Djh123456', db='scraping', port=3306, charset='utf8')
cur = conn.cursor()
cur.execute("USE scraping")
cur.execute("SELECT * FROM pages")
print(cur.fetchone())
cur.close()
conn.close()