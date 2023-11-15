FROM neomantra/flatbuffers

ENV PATH="/usr/local/bin:${PATH}"

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    gcc

# Copy build.sh, eclectic.fbs, and myissue.c from the host into an /app directory in the image
COPY build.sh eclectic.fbs myissue.c /app/

# Give permissions to the build.sh script to allow it to access the flatc and flatcc binaries
RUN chmod +x /app/build.sh

# Run build.sh
RUN /app/build.sh

# Run the myissue binary
CMD ["/app/myissue"]