from flask import Flask, request, render_template, jsonify

class SparringCounter:
    def __init__(self):
        self.red = False
        self.blue = False
        
    def reset(self):
        self.red = False
        self.blue = False
        
    def todict(self):
        return {'red':self.red, 'blue':self.blue}
        

app = Flask(__name__)
sc = SparringCounter()

@app.route('/counter/view', methods = ['GET'])
def counterView():
    return render_template('view.html')

@app.route('/counter/edit', methods = ['GET'])
def counterEdit():
    return render_template('edit.html')

@app.route('/data', methods=['GET', 'POST'])
def data():
    if request.method == 'POST':
        color = request.get_json().get('color')
        if color == 'redColor':
            sc.red = True
        elif color == 'blueColor': 
            sc.blue = True
        print(sc.red, sc.blue)
    return jsonify(sc.todict())
    
@app.route('/reset', methods=['POST'])
def reset():
    sc.reset()
    return jsonify(sc.todict())

if __name__ == '__main__': 
    app.run(host='0.0.0.0', debug=True)    
