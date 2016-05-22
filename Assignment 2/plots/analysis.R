library(tidyr)
library(dplyr)
library(RColorBrewer)
library(ggplot2)

options(digits=4)

# Format numbers:
#options(digits)

# Import and redefine some values:
data_general <- tbl_df(read.csv("csv/output_18_Maio_I003.csv"))
data_general <- data_general %>% filter(!(alg == 1 & threads == 0))
data_general <- data_general %>% mutate(threads = ifelse(threads == 0, 1, threads),
                                        proc = ifelse(proc == 0, 1, proc))
  
# Calculate Speedup:
sequential_times <- data_general %>% filter(alg == 0) %>% `$`(time)
data_general <- data_general %>%
  mutate(Speedup = sequential_times / time,
         Gops = ((2^n * log(log(2^n))) / time) / 10^9) %>%
  mutate(Efficency = Speedup / (proc * threads))
rm(sequential_times)

# Calcula efficiency:

# Transform in factors:
data_general$alg <- factor(data_general$alg)
data_general$threads <- factor(data_general$threads)
data_general$proc <- factor(data_general$proc)

# Gráfico Sequencial
data <- data_general %>% filter(alg == 0)
ggplot(data, aes(x=n, y=Gops)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="i", y="Performance (GOP/s)") +
ggsave("plots/plot_seq_perf.pdf", width=9, height=3)

# Gráfico do OpenMP - Tempo
data <- data_general %>% filter(alg == 1 & (as.numeric(threads) %% 2 == 0 | threads == 1))
ggplot(data, aes(x=n, y=Gops, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="i", y="Performance (GOP/s)") +
  guides(color=guide_legend(title="Nº de\nthreads"))
ggsave("plots/plot_mp_perf.pdf", width=9, height=3)

# Gráfico do MPI - Tempo
data <- data_general %>% filter(alg == 2 & as.numeric(proc) %% 2 == 0)
ggplot(data, aes(x=n, y=Gops, color=proc)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75, size=0.2) +
  labs(x="i", y="Performance (GOP/s)") +
  guides(color=guide_legend(title="Nº de\nprocessos"))
ggsave("plots/plot_mpi_perf.pdf", width=9, height=3)

# Gráfico do MPI/MP - Tempo
#### Geral
ggplot(data_general %>% filter(alg == 3 & (as.numeric(threads) %% 2 == 0)), aes(x=n, y=Gops, color=paste(sprintf("%02d", proc), threads, sep=" / "))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="i", y="Performance (GOP/s)") +
  guides(color=guide_legend(title="Nº de processos/\nthreads")) +
  #(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"), legend.justification=c(1,0.5), legend.position=c(1,0.5))
  ggsave("plots/plot_hybrid_perf.pdf", width=9, height=3)

ggplot(data_general %>% filter(alg == 3 & proc == 4), aes(x=n, y=Gops, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  #labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
  ggsave("plots/plot_hybrid_4_perf.pdf", width=4*1.5, height=3*1.5)

ggplot(data_general %>% filter(alg == 3 & proc == 8), aes(x=n, y=Gops, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  #labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
ggsave("plots/plot_hybrid_8_perf.pdf", width=4*1.5, height=3*1.5)

ggplot(data_general %>% filter(alg == 3 & proc == 12), aes(x=n, y=Gops, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  #labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
ggsave("plots/plot_hybrid_12_perf.pdf", width=4*1.5, height=3*1.5)

ggplot(data_general %>% filter(alg == 3 & proc == 16), aes(x=n, y=Gops, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  #labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
ggsave("plots/plot_hybrid_16_perf.pdf", width=4*1.5, height=3*1.5)


### SPEEDUP #################################################################
# Gráfico do OpenMP
data <- data_general %>% filter(alg == 1 & (as.numeric(threads) %% 2 == 0))
ggplot(data, aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="i", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads"))
ggsave("plots/plot_mp_speed.pdf", width=9, height=3)

# Gráfico do MPI
data <- data_general %>% filter(alg == 2 & as.numeric(proc) %% 2 == 0)
ggplot(data, aes(x=n, y=Speedup, color=proc)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75, size=0.2) +
  labs(x="i", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nprocessos"))
ggsave("plots/plot_mpi_speed.pdf", width=9, height=3)

#### Geral
data <- data_general %>% filter(alg == 3 & (as.numeric(threads) %% 2 == 0))
ggplot(data, aes(x=n, y=Speedup, color=paste(sprintf("%02d", proc), threads, sep=" / "))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="i", y="Speedup") +
  guides(color=guide_legend(title="Nº de processos/\nthreads")) +
  scale_y_continuous(breaks = round(seq(min(data$Speedup), max(data$Speedup), by = 1.0),1))
  #(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"), legend.justification=c(1,0.5), legend.position=c(1,0.5))
  ggsave("plots/plot_hybrid_speed.pdf", width=9, height=3)

# Gráfico do MPI/MP
ggplot(data_general %>% filter(alg == 3 & proc == 4), aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  #labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
  ggsave("plots/plot_hybrid_4_speed.pdf", width=4*1.5, height=3*1.5)

ggplot(data_general %>% filter(alg == 3 & proc == 8), aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  #labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
  ggsave("plots/plot_hybrid_8_speed.pdf", width=4*1.5, height=3*1.5)

ggplot(data_general %>% filter(alg == 3 & proc == 12), aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  #labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
  ggsave("plots/plot_hybrid_12_speed.pdf", width=4*1.5, height=3*1.5)

ggplot(data_general %>% filter(alg == 3 & proc == 16), aes(x=n, y=Speedup, color=threads)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  #labs(x="N", y="Speedup") +
  guides(color=guide_legend(title="Nº de\nthreads")) +
  ggsave("plots/plot_hybrid_16_speed.pdf", width=4*1.5, height=3*1.5)

##### Find out which has more Speedup
data_general %>% group_by(alg, proc, threads) %>% summarise(MedianSpeedup = median(Speedup)) %>% View