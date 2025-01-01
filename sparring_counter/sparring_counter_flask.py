from flask import Flask, request, render_template, jsonify, redirect, url_for

class SparringCounter:
    def __init__(self):
        self.red = False
        self.blue = False
        self.redName = ""
        self.blueName = ""
        
    def reset(self):
        self.red = False
        self.blue = False
        self.redName = ""
        self.blueName = ""
        
    def todict(self):
        return {'red':self.red, 'blue':self.blue, 'redName':self.redName, 'blueName':self.blueName}
        

app = Flask(__name__)
sc = SparringCounter()

@app.route('/setup', methods=['GET', 'POST'])
def setup():
    if request.method == "POST":
        return redirect(url_for('counterView'))
    return render_template('setup.html')

@app.route('/names', methods = ['GET', 'POST'])
def names():
    if request.method == 'POST': 
        sc.redName = request.get_json().get('redName')
        sc.blueName = request.get_json().get('blueName')
    return jsonify(sc.todict())

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
