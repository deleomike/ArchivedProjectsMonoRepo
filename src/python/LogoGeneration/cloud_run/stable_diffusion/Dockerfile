FROM pytorch/pytorch:2.0.1-cuda11.7-cudnn8-runtime

WORKDIR app

RUN apt-get update -y && \
    apt-get upgrade -y

RUN apt-get install -y git

COPY requirements.txt ./

RUN pip install -r requirements.txt