# Use Alpine Linux as the base image
FROM alpine:latest

# Install necessary build tools
RUN apk --update add \
    build-base \
    && rm -rf /var/cache/apk/*

# Copy Flatbuffers binaries and libraries from neomantra/flatbuffers image
COPY --from=neomantra/flatbuffers /usr/local/bin/flatc /usr/local/bin/flatc
COPY --from=neomantra/flatbuffers /usr/local/include/flatbuffers /usr/local/include/flatbuffers
COPY --from=neomantra/flatbuffers /usr/local/lib/libflatbuffers.a /usr/local/lib/libflatbuffers.a
COPY --from=neomantra/flatbuffers /usr/local/lib/cmake/flatbuffers /usr/local/lib/cmake/flatbuffers

# Copy Flatcc binaries and libraries from neomantra/flatbuffers image
COPY --from=neomantra/flatbuffers /usr/local/bin/flatcc /usr/local/bin/flatcc
COPY --from=neomantra/flatbuffers /usr/local/include/flatcc /usr/local/include/flatcc
COPY --from=neomantra/flatbuffers /usr/local/lib/libflatcc.a /usr/local/lib/libflatccrt.a /usr/local/lib/

# Copy build.sh, eclectic.fbs, and myissue.c from the host into an /app directory in the image
COPY build.sh eclectic.fbs myissue.c /app/

# Run build.sh
RUN /app/build.sh

# Run the myissue binary
CMD ["/app/myissue"]