from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api/v1/device', methods=["POST"])
def device_info_report():
    if 'application/text' in request.content_type:
        access_token = request.headers.get("accessToken")
        if access_token != "token123456789":
            return jsonify(status='401', content_type='application/json;charset=utf-8', content={
                "error": "Access Token is invalid"
            }), 401

        try:
            reqText = request.data.decode("utf-8")
        except:
            reqText = request.data.decode("gbk")
    else:
        return jsonify(status='400', content_type='application/json;charset=utf-8', content={
            "error": "Unsupported Content-Type"
        }), 400

    try:
        net_info = reqText
        print(net_info)
    except Exception as e:
        print(f"Error parsing parameters: {e}")
        return jsonify(status='400', content_type='application/json;charset=utf-8', content={
            "error": "Invalid request data"
        }), 400

    return jsonify(status='200', content_type='application/json;charset=utf-8', content={
        "resp": "OK"
    })

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True, port=53191)
