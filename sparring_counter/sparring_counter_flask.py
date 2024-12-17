from flask import Flask, redirect, url_for, request

class SparringCounter:
    def __init__(self):
        self.red = 0
        self.blue = 0
        
    def inc_red(self):
        self.red += 1
        
    def inc_blue(self): 
        self.blue += 1
        

app = Flask(__name__)
sc = SparringCounter()

@app.route('/counter', methods=['POST', 'GET'])
def counter():
    if request.method == 'POST':
        color = request.form['color']
        if color == 'Red':
            sc.inc_red()
        elif color == 'Blue': 
            sc.inc_blue()
        
    return f'Red: {sc.red:d} Blue: {sc.blue:d}'

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)    
